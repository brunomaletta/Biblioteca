void dfs(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) G[k].size(); i++)
		if (!vis[G[k][i].first]) dfs(G[k][i].first);
	S.push(k);
}

void scc(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) GI[k].size(); i++)
		if (!vis[GI[k][i].first]) {
			une(k, GI[k][i].first);
			scc(GI[k][i].first);
		}
}

void kosaraju() {
	for (int i = 0; i < n; i++) vis[i] = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

	build();

	for (int i = 0; i < n; i++) vis[i] = 0;
	while (S.size()) {
		int u = S.top();
		S.pop();
		if (!vis[u]) scc(u);
	}
}