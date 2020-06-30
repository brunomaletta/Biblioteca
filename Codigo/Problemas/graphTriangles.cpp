// Triangulos em Grafos
//
// get_triangles(i) encontra todos os triangulos ijk no grafo
// Custo nas arestas
// retorna {custo do triangulo, {j, k}}
//
// O(m sqrt(m) log(n)) se chamar para todos os vertices

vector<ii> g[MAX]; // {para, peso}

#warning o 'g' deve estar ordenado
vector<pair<int, ii>> get_triangles(int i) {
	vector<pair<int, ii>> tri;
	for (ii j : g[i]) {
		int a = i, b = j.f;
		if (g[a].size() > g[b].size()) swap(a, b);
		for (ii c : g[a]) if (c.f != b and c.f > j.f) {
			auto it = lower_bound(g[b].begin(), g[b].end(), make_pair(c.f, -INF));
			if (it == g[b].end() or it->f != c.f) continue;
			tri.push_back({j.s+c.s+it->s, {a == i ? b : a, c.f}});
		}
	}
	return tri;
}
