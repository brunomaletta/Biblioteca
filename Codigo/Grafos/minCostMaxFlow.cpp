// MinCostMaxFlow Papa

// min_cost_flow(s, t, f) computa o par (fluxo, custo)
// com max(fluxo) <= f que tenha min(custo)
// min_cost_flow(s, t) -> Fluxo maximo de custo minimo de s pra t
// Se tomar TLE, aleatorizar a ordem dos vertices no SPFA

template<typename T> struct mcmf {

	struct edge {
		int to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
		bool res; // se eh reversa
		T cost; // custo da unidade de fluxo
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false){}
		edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
			: to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_){}
	};

	vector<vector<edge>> g;
	vector<int> par_idx, par;

	mcmf(int n) : g(n), par_idx(n), par(n) {}

	void add(int u, int v, int w, T cost) { // de u pra v com cap w e custo cost
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);

		g[u].push_back(a);
		g[v].push_back(b);
	}

	bool spfa(int s, int t) {
		deque<int> q;
		vector<bool> is_inside(g.size(), 0);
		T inf = numeric_limits<T>::max() / 3;
		vector<T> dist(g.size(), inf);

		dist[s] = 0;
		is_inside[s] = true;
		q.push_back(s);

		while (!q.empty()) {
			int u = q.front();
			is_inside[u] = false;
			q.pop_front();

			for (int i = 0; i < (int)g[u].size(); i++)
				if (g[u][i].cap > g[u][i].flow && dist[u] + g[u][i].cost < dist[g[u][i].to]) {
					dist[g[u][i].to] = dist[u] + g[u][i].cost;
					par_idx[g[u][i].to] = i;
					par[g[u][i].to] = u;

					if (is_inside[g[u][i].to]) continue;
					if (!q.empty() && dist[g[u][i].to] > dist[q.front()]) q.push_back(g[u][i].to);
					else q.push_front(g[u][i].to);

					is_inside[g[u][i].to] = true;
				}
		}

		return dist[t] != inf;
	}

	pair<int, T> min_cost_flow(int s, int t, int flow = INF) {
		int f = 0;
		T ret = 0;
		while (f <= flow && spfa(s, t)) {
			int mn_flow = flow - f, u = t;
			while (u != s){
				mn_flow = min(mn_flow, g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
				u = par[u];
			}

			u = t;
			while (u != s) {
				g[par[u]][par_idx[u]].flow += mn_flow;
				g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
				ret += g[par[u]][par_idx[u]].cost * mn_flow;
				u = par[u];
			}

			f += mn_flow;
		}

		return make_pair(f, ret);
	}

	// Opicional: Retorna todas as arestas originais por onde passa fluxo = capacidade.
	vector<pair<int,int>> recover() {
		vector<pair<int,int>> used;
		for (int i = 0; i < g.size(); i++) for (edge e : g[i])
			if(e.flow == e.cap && !e.res) used.push_back({i, e.to});
		return used;
	}
};
