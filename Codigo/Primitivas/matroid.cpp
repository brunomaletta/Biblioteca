// Matroid
//
// Matroids de Grafo e Particao
// De modo geral, toda Matroid contem um build() linear
// e uma funcao constante oracle()
// oracle(i) responde se o conjunto continua independente 
// apos adicao do elemento i
// oracle(i, j) responde se o conjunto continua indepente
// apos trocar o elemento i pelo elemento j
//
// Intersecao sem peso O(r^2 n)
// em que n eh o tamanho do conjunto e r eh o tamanho da resposta

// Matroid Grafica
// Matroid das florestas de um grafo
// Um conjunto de arestas eh independente se formam uma floresta
//
// build() : O(n)
// oracle() : O(1)

struct graphic_matroid {
	int n, m, t;
	vector<array<int, 2>> edges;
	vector<vector<int>> g;
	vector<int> comp, in, out;
	graphic_matroid(int n_, vector<array<int, 2>> edges_) 
		: n(n_), m(edges_.size()), edges(edges_), g(n), comp(n), in(n), out(n) {}
	void dfs(int u) {
		in[u] = t++;
		for (auto v : g[u]) if (in[v] == -1)
			comp[v] = comp[u], dfs(v);
		out[u] = t;
	}
	void build(vector<int> I) {
		t = 0;
		for (int u = 0; u < n; u++) g[u].clear(), in[u] = -1;
		for (int e : I) {
			auto [u, v] = edges[e];
			g[u].push_back(v), g[v].push_back(u);
		}
		for (int u = 0; u < n; u++) if (in[u] == -1)
			comp[u] = u, dfs(u);
	}
	bool is_ancestor(int u, int v) {
		return in[u] <= in[v] and in[v] < out[u];
	}
	bool oracle(int e) {
		return comp[edges[e][0]] != comp[edges[e][1]];
	}
	bool oracle(int e, int f) {
		if (oracle(f)) return true;
		int u = edges[e][in[edges[e][0]] < in[edges[e][1]]];
		return is_ancestor(u, edges[f][0]) != is_ancestor(u, edges[f][1]);
	}
};

// Matroid de particao ou cores
// Um conjunto eh independente se a quantidade de elementos
// de cada cor nao excede a capacidade da cor
// Quando todas as capacidades sao 1, um conjunto eh independente
// se todas as suas cores sao distintas
// 
// build() : O(n)
// oracle() : O(1)

struct partition_matroid {
	vector<int> cap, color, d;
	partition_matroid(vector<int> cap_, vector<int> color_) 
		: cap(cap_), color(color_), d(cap.size()) {}
	void build(vector<int> I) {
		fill(d.begin(), d.end(), 0);
		for (int u : I) d[color[u]]++;
	}
	bool oracle(int u) {
		return d[color[u]] < cap[color[u]];
	}
	bool oracle(int u, int v) {
		return color[u] == color[v] or oracle(v);
	}
};

// Intersecao de matroid sem pesos
// Dadas duas matroids M1 e M2 definidas sobre o mesmo
// conjunto I, retorna o maior subconjunto de I
// que eh independente tanto para M1 quanto para M2
//
// O(r^2*n)

// Matroid "pesada" deve ser a M2
template<typename Matroid1, typename Matroid2>
vector<int> matroid_intersection(int n, Matroid1 M1, Matroid2 M2) {
	vector<bool> b(n);
	vector<int> I[2];
	bool converged = false;
	while (!converged) {
		I[0].clear(), I[1].clear();
		for (int u = 0; u < n; u++) I[b[u]].push_back(u);

		M1.build(I[1]), M2.build(I[1]);
		vector<bool> target(n), pushed(n);
		queue<int> q;
		for (int u : I[0]) {
			target[u] = M2.oracle(u);
			if (M1.oracle(u)) pushed[u] = true, q.push(u);
		}
		vector<int> p(n, -1);
		converged = true;
		while (q.size()) {
			int u = q.front(); q.pop();
			if (target[u]) {
				converged = false;
				for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
				break;
			}
			for (int v : I[!b[u]]) if (!pushed[v]) {
				if ((b[u] and M1.oracle(u, v)) or (b[v] and M2.oracle(v, u)))
					p[v] = u, pushed[v] = true, q.push(v);
			}
		}
	}
	return I[1];
}

// Intersecao de matroid com pesos
// Dadas duas matroids M1 e M2 e uma funcao de pesos w, todas definidas sobre
// um conjunto I retorna o maior subconjunto de I (desempatado pelo menor peso)
// que eh independente tanto para M1 quanto para M2
// A resposta eh construida incrementando o tamanho conjunto I de 1 em 1
// Se nao tiver custo negativo, nao precisa de SPFA
//
// O(r^3*n) com SPFA
// O(r^2*n*log(n)) com Dijkstra e potencial

template<typename T, typename Matroid1, typename Matroid2>
vector<int> weighted_matroid_intersection(int n, vector<T> w, Matroid1 M1, Matroid2 M2) {
	vector<bool> b(n), target(n), is_inside(n);
	vector<int> I[2], from(n);
	vector<pair<T, int>> d(n);
	auto check_edge = [&](int u, int v) {
		return (b[u] and M1.oracle(u, v)) or (b[v] and M2.oracle(v, u));
	};
	while (true) {
		I[0].clear(), I[1].clear();
		for (int u = 0; u < n; u++) I[b[u]].push_back(u);
		// I[1] contem o conjunto de tamanho I[1].size() de menor peso
		M1.build(I[1]), M2.build(I[1]);
		for (int u = 0; u < n; u++) {
			target[u] = false, is_inside[u] = false, from[u] = -1;
			d[u] = {numeric_limits<T>::max(), INF};
		}
		deque<T> q;
		sort(I[0].begin(), I[0].end(), [&](int i, int j){ return w[i] < w[j]; });
		for (int u : I[0]) {
			target[u] = M2.oracle(u);
			if (M1.oracle(u)) {
				if (is_inside[u]) continue;
				d[u] = {w[u], 0};
				if (!q.empty() and d[u] > d[q.front()]) q.push_back(u);
				else q.push_front(u);
				is_inside[u] = true;
			}
		}	
		while (q.size()) {
			int u = q.front(); q.pop_front();
			is_inside[u] = false;
			for (int v : I[!b[u]]) if (check_edge(u, v)) {
				pair<T, int> nd(d[u].first + w[v], d[u].second + 1);
				if (nd < d[v]) {
					from[v] = u, d[v] = nd;
					if (is_inside[v]) continue;
					if (q.size() and d[v] > d[q.front()]) q.push_back(v);
					else q.push_front(v);
					is_inside[v] = true;
				}
			}
		}
		pair<T, int> mini = pair(numeric_limits<T>::max(), INF);
		int targ = -1;
		for (int u : I[0]) if (target[u] and d[u] < mini) 
			mini = d[u], targ = u;	
		if (targ != -1) for (int u = targ; u != -1; u = from[u])
			b[u] = !b[u], w[u] *= -1;
		else break;
	}
	return I[1];
}
