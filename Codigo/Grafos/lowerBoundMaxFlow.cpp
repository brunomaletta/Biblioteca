// Max flow com lower bound
// 
// add(a, b, l, r):
// 	adiciona aresta de a pra b, onde precisa passar f de fluxo, l <= f <= r
// add(a, b, c):
// 	adiciona aresta de a pra b com capacidade c
//
// Mesma complexidade do Dinitz

struct lb_max_flow : dinitz {
	vector<int> d;
	lb_max_flow(int n) : dinitz(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		dinitz::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		dinitz::add(a, b, c);
	}
	bool has_circulation() {
		int n = d.size();

		ll cost = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > 0) {
				cost += d[i];
				dinitz::add(n, i, d[i]);
			} else if (d[i] < 0) {
				dinitz::add(i, n+1, -d[i]);
			}
		}

		return (dinitz::max_flow(n, n+1) == cost);
	}
	bool has_flow(int src, int snk) {
		dinitz::add(snk, src, INF);
		return has_circulation();
	}
	ll max_flow(int src, int snk) {
		if (!has_flow(src, snk)) return -1;
		dinitz::F = 0;
		return dinitz::max_flow(src, snk);
	}
};
