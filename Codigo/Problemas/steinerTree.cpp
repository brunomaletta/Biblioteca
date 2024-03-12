// Steiner Tree
//
// steiner: retorna o peso da menor arvore que cobre os vertices S
// get_steiner: retorna o valor minimo e as arestas de uma solucao
// se nao tiver solucao retorna LINF
//
// grafo nao pode ter pesos negativos
// se so tiver peso nas arestas/vertices pode deletar os vw/w no codigo
//
// k = |S|
// O(3^k * n + 2^k * m log m)

// otimizacao: joga um vertice x do S fora e pegue a resposta em dp[...][x] e reconstrua a arvore a partir dele
// ta comentado no codigo as mudancas necessarias

int n; // numero de vertices
vector<pair<int, int>> g[MAX]; // {vizinho, peso}
ll d[1 << K][MAX]; // dp[mask][v] = arvore minima com o subconjunto mask de S e o vertice v
ll vw[MAX]; // peso do vertice

ll steiner(const vector<int> &S) {
	int k = S.size(); // k--;
	for (int mask = 0; mask < (1 << k); mask++) for(int v = 0; v < n; v++) d[mask][v] = LINF;
	for (int v = 0; v < n; v++) d[0][v] = vw[v];
	for (int i = 0; i < k; ++i) d[1 << i][S[i]] = vw[S[i]];
	for (int mask = 1; mask < (1 << k); mask++) {
		for (int a = (mask - 1) & mask; a; a = (a - 1) & mask) {
			int b = mask ^ a;
			if (b > a) break;
			for (int v = 0; v < n; v++)
				d[mask][v] = min(d[mask][v], d[a][v] + d[b][v] - vw[v]);
		}
		priority_queue<pair<ll, int>> pq;
		for (int v = 0; v < n; v++) {
			if (d[mask][v] == LINF) continue;
			pq.emplace(-d[mask][v], v);
		}
		while (pq.size()) {
			auto [ndist, u] = pq.top(); pq.pop();
			if (-ndist > d[mask][u]) continue;
			for (auto [idx, w] : g[u]) if (d[mask][idx] > d[mask][u] + w + vw[idx]) {
				d[mask][idx] = d[mask][u] + w + vw[idx];
				pq.emplace(-d[mask][idx], idx);
			}
		}
	}
	return d[(1 << k) - 1][S[0]]; // S[k]
}

#warning se k=1 a solucao eh a folha isolada e a funcao retorna edg = {}
#warning se k=0 crasha
pair<ll,vector<pair<int,int>>> get_steiner(const vector<int> &S) {
	int k = S.size(); // k--;
	ll ans = steiner(S);
	vector<pair<int,int>> edg;
	stack<pair<int,int>> stk;
	stk.emplace((1 << k) - 1, S[0]); // S[k]
	while (!stk.empty()) {
		bool cont = 0;
		auto [mask,u] = stk.top();stk.pop();
		if ((__builtin_popcount(mask) == 1 and u == S[__bit_width(mask) - 1])) continue;
		for (auto [idx, w] : g[u]){
			if (d[mask][u] == d[mask][idx] + w + vw[u]) {
				edg.emplace_back(u, idx);
				stk.emplace(mask, idx);
				cont = true;
				break;
			}
		}
		if (cont) continue;
		for (int a = (mask - 1) & mask; a; a = (a - 1) & mask) {
			int b = mask ^ a;
			if (d[mask][u] == d[a][u] + d[b][u] - vw[u]) {
				stk.emplace(a, u);
				stk.emplace(b, u);
				cont = true;
				break;
			}
		}
		assert(!mask || cont);
	}
	return {ans, edg};
}
