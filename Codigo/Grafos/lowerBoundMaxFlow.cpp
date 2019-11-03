// Max flow com lower bound nas capacidades
//
// O(dinic)

struct lb_max_flow : dinic {
	vector<int> d;
	vector<int> e;
	lb_max_flow(int n):dinic(n + 2), d(n, 0){}
	void add(int a, int b, int c, int lb = 0){
		c -= lb;
		d[a] -= lb;
		d[b] += lb;
		dinic::add(a, b, c);
	}
	bool check_flow(int src, int snk, int F){
		int n = d.size();
		d[src] += F;
		d[snk] -= F;

		for (int i = 0; i < n; i++){
			if (d[i] > 0){
				dinic::add(n, i, d[i]);
			} else if (d[i] < 0){
				dinic::add(i, n+1, -d[i]);
			}
		}

		int f = max_flow(n, n+1);
		return (f == F);
	}
};
