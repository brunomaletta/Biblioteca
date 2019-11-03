// MinCostMaxFlow Papa

/*
   s e t pre-definidos como MAXN - 1 e MAXN - 2.
   minCostFlow(f) computa o par (fluxo, custo) com max(fluxo) <= f que tenha min(custo).
   minCostFlow(INF) -> Fluxo maximo de custo minimo.
   Se tomar TLE, aleatorizar a ordem dos vertices no SPFA
 */

const int MAXN = 230;

template<typename T> struct MCMF {
	
	struct edge {
		int to, rev, flow, cap, residual;
		T cost;
		edge() { to = 0; rev = 0; flow = 0; cap = 0; cost = 0; residual = false; }
		edge(int _to, int _rev, int _flow, int _cap, T _cost, bool _residual) {
			to = _to; rev = _rev;
			flow = _flow; cap = _cap;
			cost = _cost;
			residual = _residual;
		}
	};

	int s = MAXN - 1, t = MAXN - 2;
	vector<edge> G[MAXN];

	void addEdge(int u, int v, int w, T cost) {
		edge t = edge(v, G[v].size(), 0, w, cost, false);
		edge r = edge(u, G[u].size(), 0, 0, -cost, true);

		G[u].push_back(t);
		G[v].push_back(r);
	}

	deque<int> Q;
	bool is_inside[MAXN];
	int par_idx[MAXN], par[MAXN];
	T dist[MAXN];
	bool spfa() {
		for(int i = 0; i < MAXN; i++)
			dist[i] = INF;
		dist[t] = INF;

		Q.clear();
		dist[s] = 0;
		is_inside[s] = true;
		Q.push_back(s);

		while(!Q.empty()) {
			int u = Q.front();
			is_inside[u] = false;
			Q.pop_front();

			for(int i = 0; i < (int)G[u].size(); i++)
				if(G[u][i].cap > G[u][i].flow && dist[u] + G[u][i].cost < dist[G[u][i].to]) {
					dist[G[u][i].to] = dist[u] + G[u][i].cost;
					par_idx[G[u][i].to] = i;
					par[G[u][i].to] = u;

					if(is_inside[G[u][i].to]) continue;
					if(!Q.empty() && dist[G[u][i].to] > dist[Q.front()]) Q.push_back(G[u][i].to);
					else Q.push_front(G[u][i].to);

					is_inside[G[u][i].to] = true;
				}
		}

		return dist[t] != INF;
	}

	pair<int, T>  minCostFlow(int flow) {
		int f = 0;
		T ret = 0;
		while(f <= flow && spfa()) {
			int mn_flow = flow - f, u = t;
			while(u != s){
				mn_flow = min(mn_flow, G[par[u]][par_idx[u]].cap - G[par[u]][par_idx[u]].flow);
				u = par[u];
			}

			u = t;
			while(u != s) {
				G[par[u]][par_idx[u]].flow += mn_flow;
				G[u][G[par[u]][par_idx[u]].rev].flow -= mn_flow;
				ret += G[par[u]][par_idx[u]].cost * mn_flow;
				u = par[u];
			}

			f += mn_flow;
		}

		return make_pair(f, ret);
	}

	/*
	   Opcional.
	   Retorna todas as arestas originais por onde passa fluxo = capacidade.
	 */
	vector<pair<int ,int > > recover() {
		vector<pair<int, int > > used;
		for(int i = 0; i < MAXN; i++) 
			for(edge e : G[i])
				if(e.flow == e.cap && !e.residual)
					used.push_back({i, e.to});
		return used;
	}
};
