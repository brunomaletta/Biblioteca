// Centro da Arvore
//
// Centro eh o vertice que minimiza
// a maior distancia dele pra alguem
// O centro fica no meio do diametro
// A funcao center retorna um par com
// o diametro e o centro
//
// O(n+m)

vector<vector<int> > g(MAX);
int n, vis[MAX];
int d[2][MAX];

// retorna ultimo vertice visitado
int bfs(int k, int x) {
        queue<int> q; q.push(k);
	memset(vis, 0, sizeof(vis));
	vis[k] = 1;
	d[x][k] = 0;
	int last = k;
	
	while (q.size()) {
		int u = q.front(); q.pop();
		last = u;
		for (int i : g[u]) if (!vis[i]) {
			vis[i] = 1;
			q.push(i);
			d[x][i] = d[x][u] + 1;
		}
	}
	return last;
}

pair<int, int> center() {
	int a = bfs(0, 0);
	int b = bfs(a, 1);
	bfs(b, 0);
	int c, mi = INF;
	for (int i = 0; i < n; i++) if (max(d[0][i], d[1][i]) < mi) {
		mi = max(d[0][i], d[1][i]), c = i;
	return {d[0][a], c};
}
