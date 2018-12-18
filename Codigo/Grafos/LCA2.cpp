// LCA com HLD
//
// Assume que um vertice eh ancestral dele mesmo, ou seja,
// se a eh ancestral de b, LCA(a, b) = b
// Para buildar pasta chamar build(root)
//
// Complexidades:
// build - O(n)
// lca - O(log(n))

vector<vector<int> > g(MAX);
int in[MAX], h[MAX], sz[MAX];
int pai[MAX], t;

void build(int k, int p = -1, int f = 0) {
	in[k] = t++; sz[k] = 1;
	for (int& i : g[k]) if (i != p) {
		h[i] = (i == g[k][0] ? h[k] : i);
		build(i, k, f);
		sz[k] += sz[i]; pai[i] = k;
		if (sz[i] > sz[g[k][0]]) swap(i, g[k][0]);
	}
	if (p*!f == -1) t = 0, h[k] = k, build(k, -1, 1);
}


int lca(int a, int b) {
	if (in[a] < in[b]) swap(a, b);
	return h[a] == h[b] ? b : lca(pai[h[a]], b);
}
