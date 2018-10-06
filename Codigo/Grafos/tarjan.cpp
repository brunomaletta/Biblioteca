// Algoritmo de Tarjan para SCC
//
// O(n + m)

int n;
vector<vector<int> > g(MAX);
stack<int> S;
int vis[MAX], comp[MAX];
int id[MAX], p;

int dfs(int k) {
	int lo = id[k] = p++;
	S.push(k);
	vis[k] = 2; // ta na pilha

	// calcula o menor cara q ele alcanca
	// que ainda nao esta em um scc
	for (int i = 0; i < sz(g[k]); i++) {
	 	if (!vis[g[k][i]])
			lo = min(lo, dfs(g[k][i]));
		else if (vis[g[k][i]] == 2)
			lo = min(lo, id[g[k][i]]);
	}

	// nao alcanca ninguem menor -> comeca scc
	if (lo == id[k]) while (1) {
		int u = S.top();
		S.pop(); vis[u] = 1;
		comp[u] = k;
		if (u == k) break;
	}

	return lo;
}

void tarjan() {
	memset(vis, 0, sizeof(vis));

	p = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
}
