// Centro de arvore
//
// Retorna o diametro e o(s) centro(s) da arvore
// Uma arvore tem sempre um ou dois centros e estes estao no meio do diametro
//
// O(n)

vector<int> g[MAX];
int d[MAX], par[MAX];

pair<int, vector<int>> center() {
	int f, df;
	function<void(int)> dfs = [&] (int v) {
		if (d[v] > df) f = v, df = d[v];
		for (int u : g[v]) if (u != par[v]) 
			d[u] = d[v] + 1, par[u] = v, dfs(u);
	};
 
	f = df = par[0] = -1, d[0] = 0;
	dfs(0);
	int root = f;
	f = df = par[root] = -1, d[root] = 0;
	dfs(root);
 
 	vector<int> c;
	while (f != -1) {
		if (d[f] == df/2 or d[f] == (df+1)/2) c.push_back(f);
		f = par[f];
	}
 
	return {df, c};
}
