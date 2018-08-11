// LCA com RMQ
//
// Assume que um vertice é ancestral dele mesmo, ou seja,
// se a é ancestral de b, LCA(a, b) = b
//
// Complexidades:
// build - O(n) + build_RMQ
// lca - RMQ
 
int n;
vector<vector<int> > g(MAX);
int pos[MAX];     // pos[i] : posicao de i em v (primeira aparicao
int ord[2 * MAX]; // ord[i] : i-esimo vertice na ordem de visitacao da dfs
int v[2 * MAX];   // vetor de alturas que eh usado na RMQ
int p;
 
void dfs(int k, int l) {
	ord[p] = k;
	pos[k] = p;
	v[p++] = l;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (pos[g[k][i]] == -1) {
			dfs(g[k][i], l + 1);
			ord[p] = k;
			v[p++] = l;
		}
}
 
void build(int root) {
	for (int i = 0; i < n; i++) pos[i] = -1;

	p = 0;
	dfs(root, 0);

	build_RMQ();
}
 
int lca(int u, int v) {
	int a = pos[u], b = pos[v];
	if (a > b) swap(a, b);
	return ord[RMQ(a, b)];
}
