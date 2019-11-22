// Line Tree
//
// Reduz min-query em arvore para RMQ
// Se o grafo nao for uma arvore, as queries
// sao sobre a arvore geradora maxima
// Queries de minimo
//
// build - O(n log(n))
// query - O(log(n))

int n;

namespace linetree {
	int id[MAX], seg[2*MAX], pos[MAX];
	vector<int> v[MAX], val[MAX];
	vector<pair<int, pair<int, int> > > ar;

	void add(int a, int b, int p) { ar.pb({p, {a, b}}); }
	void build() {
		sort(ar.rbegin(), ar.rend());
		for (int i = 0; i < n; i++) id[i] = i, v[i] = {i}, val[i].clear();
		for (auto i : ar) {
			int a = id[i.second.first], b = id[i.second.second];
			if (a == b) continue;
			if (v[a].size() < v[b].size()) swap(a, b);
			for (auto j : v[b]) {
				id[j] = a;
				v[a].push_back(j);
			}
			val[a].push_back(i.first);
			for (auto j : val[b]) val[a].push_back(j);
			v[b].clear(), val[b].clear();
		}
		for (int i = 0; i < n; i++) pos[v[id[0]][i]] = i;
		for (int i = n; i < 2*n-1; i++) seg[i] = val[id[0]][i-n];
		seg[2*n-1] = INF;
		for (int i = n-1; i > 0; i--) seg[i] = min(seg[2*i], seg[2*i+1]);
	}
	int query(int a, int b) {
		a = pos[a]+n, b = pos[b]+n;
		if (a > b) swap(a, b);
		int ans = INF; b--;
		for (; a <= b; ++a/=2, --b/=2) ans = min({ans, seg[a], seg[b]});
		return ans;
	}
};
