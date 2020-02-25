// Dinic (Bruno)
//
// O(n^2 m)
// Grafo com capacidades 1 -> O(sqrt(n)*m)

struct dinic {
	struct edge {
		int to, cap, rev, flow; // para, capacidade, id da reversa, fluxo
		bool res; // se a aresta eh residual
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev;
	dinic(int n): g(n){}

	void add(int a, int b, int c) { // de a pra b com cap. c
		g[a].pb(edge(b, c, g[b].size(), false));
		g[b].pb(edge(a, 0, g[a].size()-1, true));
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				lev[i.to] = lev[u] + 1;
				if (i.to == t) return 1;
				q.push(i.to);
			}
		}
		return 0;
	}
	int dfs(int v, int s, int f = INF){
		if (v == s) return f;
		int tem = f;
		for (auto& i : g[v]) {
			if (lev[i.to] != lev[v] + 1 or (i.flow == i.cap)) continue;
			int foi = dfs(i.to, s, min(tem, i.cap - i.flow));
			tem -= foi, i.flow += foi, g[i.to][i.rev].flow -= foi;
		}
		if (f == tem) lev[v] = -1;
		return f - tem;
	}
	int max_flow(int s, int t) {
		int f = 0;
		while (bfs(s, t)) f += dfs(s, t);
		return f;
	}
	vector<pair<int, int> > get_cut(int s, int t) {
		max_flow(s, t);
		vector<pair<int, int> > cut;
		vector<int> vis(g.size(), 0), st = {s};
		vis[s] = 1;
		while (st.size()) {
			int u = st.back(); st.pop_back();
			for (auto e : g[u]) if (!vis[e.to] and e.flow < e.cap) {
				vis[e.to] = 1;
				st.push_back(e.to);
			}
		}
		for (int i = 0; i < g.size(); i++) for (auto e : g[i])
			if (vis[i] and !vis[e.to] and !e.res) cut.push_back({i, e.to});
		return cut;
	}
};
