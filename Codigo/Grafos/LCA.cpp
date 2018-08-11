// LCA
//
// Assume que um vertice é ancestral dele mesmo, ou seja,
// se a é ancestral de b, LCA(a, b) = b
// MAXP = ceil(log(MAX))
//
// Complexidades:
// build - O(n log(n))
// lca - O(log(n))

int n;
vector<vector<int> > g(MAX); // grafo ja montado
int pai[MAXP][MAX];          // pai[k][i] : (2^k)-esimo pai de i
int level[MAX];

void dfs(int k, int l) {
	level[k] = l;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (level[g[k][i]] == -1) {
			pai[0][g[k][i]] = k;
			dfs(g[k][i], l + 1);
		}
}

void build(int raiz) {
	for (int i = 0; i < n; i++) pai[0][i] = i;
	for (int i = 0; i < n; i++) level[i] = -1;

	dfs(raiz, 0);

	// pd dos pais
	for (int k = 1; k < MAXP; k++)
		for (int i = 0; i < n; i++)
			pai[k][i] = pai[k - 1][pai[k - 1][i]];
}

int lca(int a, int b) {
	if (level[a] < level[b]) swap(a, b);

	// iguala altura
	for (int k = MAXP - 1; k >= 0; k--)
		if (level[pai[k][a]] > level[b])
			a = pai[k][a];

	if (level[a] != level[b]) a = pai[0][a];

	// sobe ate o lca
	for (int k = MAXP - 1; k >= 0; k--)
		if (pai[k][a] != pai[k][b]) {
			a = pai[k][a];
			b = pai[k][b];
		}

	if (a != b) a = pai[0][a];

	return a;
}
