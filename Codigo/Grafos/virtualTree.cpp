// Virtual Tree
//
// Comprime uma arvore dado um conjunto S de vertices, de forma que
// o conjunto de vertices da arvore comprimida contenha S e seja
// minimal e fechado sobre a operacao de LCA
// Se |S| = k, a arvore comprimida tem O(k) vertices
//
// O(k log(k))
// 402aff

vector<int> virt[MAX];

#warning lembrar de buildar o LCA antes
int build_virt(vector<int> v) {
	auto cmp = [&](int i, int j) { return lca::pos[i] < lca::pos[j]; };
	sort(v.begin(), v.end(), cmp);
	for (int i = v.size()-1; i; i--) v.push_back(lca::lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i : v) virt[i].clear();
	for (int i = 1; i < v.size(); i++) {
#warning soh to colocando aresta descendo
		virt[lca::lca(v[i-1], v[i])].push_back(v[i]);
	}
	return v[0];
}
