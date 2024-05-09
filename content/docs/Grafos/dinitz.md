---
weight: 10
title: "Dinitz"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 O(min(m * max_flow, n^2 m))

 Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))

 Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))



Link original: [dinitz.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/dinitz.cpp)

## Código
```cpp
struct dinitz {
	const bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

// Recupera as arestas do corte s-t
vector<pair<int, int>> get_cut(dinitz& g, int s, int t) {
	g.max_flow(s, t);
	vector<pair<int, int>> cut;
	vector<int> vis(g.g.size(), 0), st = {s};
	vis[s] = 1;
	while (st.size()) {
		int u = st.back(); st.pop_back();
		for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
			vis[e.to] = 1, st.push_back(e.to);
	}
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (vis[i] and !vis[e.to] and !e.res) cut.emplace_back(i, e.to);
	return cut;
}
```
