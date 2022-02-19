// Max flow com lower bound nas arestas
// 
// add(a, b, l, r):
// 	adiciona aresta de a pra b, onde precisa passar f de fluxo, l <= f <= r
// add(a, b, c):
// 	adiciona aresta de a pra b com capacidade c
//
// Mesma complexidade do Dinic
// 3f0b15

struct lb_max_flow : dinic {
	vector<int> d;
	lb_max_flow(int n) : dinic(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		dinic::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		dinic::add(a, b, c);
	}
	bool has_circulation() {
		int n = d.size();

		ll cost = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > 0) {
				cost += d[i];
				dinic::add(n, i, d[i]);
			} else if (d[i] < 0) {
				dinic::add(i, n+1, -d[i]);
			}
		}

		return (max_flow(n, n+1) == cost);
	}
	bool has_flow(int src, int snk) {
		dinic::add(snk, src, INF);
		return has_circulation();
	}
};
