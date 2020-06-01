// Distinct Range Query - Wavelet
//
// build - O(n (log n + log(sigma)))
// query - O(log(sigma))

int v[MAX], n, nxt[MAX];

namespace wav {
	vector<int> esq[4*(1+MAXN-MINN)];

	void build(int b = 0, int e = n, int p = 1, int l = MINN, int r = MAXN) {
		if (l == r) return;
		int m = (l+r)/2; esq[p].push_back(0);
		for (int i = b; i < e; i++) esq[p].push_back(esq[p].back()+(nxt[i]<=m));
		int m2 = stable_partition(nxt+b, nxt+e, [=](int i){return i <= m;}) - nxt;
		build(b, m2, 2*p, l, m), build(m2, e, 2*p+1, m+1, r);
	}

	int count(int i, int j, int x, int y, int p = 1, int l = MINN, int r = MAXN) {
		if (y < l or r < x) return 0;
		if (x <= l and r <= y) return j-i;
		int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
		return count(ei, ej, x, y, 2*p, l, m)+count(i-ei, j-ej, x, y, 2*p+1, m+1, r);
	}
}

void build() {
	for (int i = 0; i < n; i++) nxt[i] = MAXN+1;
	vector<ii> t;
	for (int i = 0; i < n; i++) t.push_back({v[i], i});
	sort(t.begin(), t.end());
	for (int i = 0; i < n-1; i++) if (t[i].f == t[i+1].f) nxt[t[i].s] = t[i+1].s;

	wav::build();
}

int query(int a, int b) {
	return wav::count(a, b+1, b+1, MAXN+1);
}
