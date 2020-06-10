// Tarjan para SCC
//
// O(n + m)

int n;
vector<int> g[MAX];
stack<int> s;
int vis[MAX], comp[MAX];
int id[MAX], p;

// se quiser comprimir ciclo em grafo nao direcionado,
// colocar um if na dfs para nao voltar pro vertice que veio
int dfs(int k) {
	int lo = id[k] = p++;
	s.push(k);
	vis[k] = 2; // ta na pilha

	// calcula o menor cara q ele alcanca
	// que ainda nao esta em um scc
	for (int i = 0; i < g[k].size(); i++) {
	 	if (!vis[g[k][i]])
			lo = min(lo, dfs(g[k][i]));
		else if (vis[g[k][i]] == 2)
			lo = min(lo, id[g[k][i]]);
	}

	// nao alcanca ninguem menor -> comeca scc
	if (lo == id[k]) while (1) {
		int u = s.top();
		s.pop(); vis[u] = 1;
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
