// Dinic (Dilson)
//
// O(n^2 m)
// Grafo bipartido -> O(sqrt(n)*m)

template <class T> struct dinic {
	struct edge {
		int v, rev;
		T cap;
		edge(int v_, T cap_, int rev_) : v(v_), cap(cap_), rev(rev_) {}
	};
	vector<vector<edge>> g;
	vector<int> level;
	queue<int> q;
	T flow;
	int n;
	dinic(int n_) : g(n_), level(n_), n(n_) {}
	void add_edge(int u, int v, T cap) {
		if (u == v)
			return;
		edge e(v, cap, int(g[v].size()));
		edge r(u, 0, int(g[u].size()));
		g[u].push_back(e);
		g[v].push_back(r);
	}

	bool build_level_graph(int src, int sink) {
		fill(level.begin(), level.end(), -1);
		while (not q.empty())
			q.pop();
		level[src] = 0;
		q.push(src);
		while (not q.empty()) {
			int u = q.front();
			q.pop();
			for (auto e = g[u].begin(); e != g[u].end(); ++e) {
				if (not e->cap or level[e->v] != -1)
					continue;
				level[e->v] = level[u] + 1;
				if (e->v == sink)
					return true;
				q.push(e->v);
			}
		}
		return false;
	}

	T blocking_flow(int u, int sink, T f) {
		if (u == sink or not f)
			return f;
		T fu = f;
		for (auto e = g[u].begin(); e != g[u].end(); ++e) {
			if (not e->cap or level[e->v] != level[u] + 1)
				continue;
			T mincap = blocking_flow(e->v, sink, min(fu, e->cap));
			if (mincap) {
				g[e->v][e->rev].cap += mincap;
				e->cap -= mincap;
				fu -= mincap;
			}
		}
		if (f == fu)
			level[u] = -1;
		return f - fu;
	}
	T max_flow(int src, int sink) {
		flow = 0;
		while (build_level_graph(src, sink))
			flow += blocking_flow(src, sink, numeric_limits<T>::max());
		return flow;
	}
};

