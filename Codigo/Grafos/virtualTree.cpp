// Virtual Tree
//
// Comprime uma arvore dado um conjunto S de vertices, de forma que
// o conjunto de vertices da arvore comprimida contenha S e seja
// minimal e fechado sobre a operacao de LCA
// Se |S| = k, a arvore comprimida tem menos que 2k vertices
// As arestas de virt possuem a distancia do vertice ate o vizinho
//
// O(k log(k))
// 487984

vector<pair<int, int>> virt[MAX];

#warning lembrar de buildar o LCA antes
int built_virt(vector<int> v) {
	auto cmp = [&](int i, int j) { return lca::pos[i] < lca::pos[j]; };
	sort(v.begin(), v.end(), cmp);
	for (int i = v.size()-1; i; i--) v.push_back(lca::lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < v.size(); i++) virt[v[i]].clear();
	for (int i = 1; i < v.size(); i++) virt[lca::lca(v[i-1], v[i])].clear();
	for (int i = 1; i < v.size(); i++) {
		int l = lca::lca(v[i-1], v[i]);
		int d = lca::dist(l, v[i]);
		virt[l].emplace_back(v[i], d);
		virt[v[i]].emplace_back(l, d);
	}
	return v[0];
}

