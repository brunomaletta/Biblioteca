// Distinct Range Query - Persistent Segtree
//
// build - O(n (log n + log(sigma)))
// query - O(log(sigma))

const int MAX = 3e4+10, LOG = 20;
const int MAXS = 4*MAX+MAX*LOG;

namespace perseg {
	ll seg[MAXS];
	int rt[MAX], L[MAXS], R[MAXS], cnt, t;
	int n, *v;

	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = 0;
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2) {
		n = n2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	ll query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return query(a, b, L[p], l, m) + query(a, b, R[p], m+1, r);
	}
	ll query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	ll update(int a, int x, int lp, int p, int l, int r) {
		if (l == r) return seg[p] = seg[lp]+x;

		int m = (l+r)/2;
		if (a <= m)
			return seg[p] = update(a, x, L[lp], L[p]=cnt++, l, m) + seg[R[p]=R[lp]];
		return seg[p] = seg[L[p]=L[lp]] + update(a, x, R[lp], R[p]=cnt++, m+1, r);
	}
	void update(int a, int x, int tt=t) {
		update(a, x, rt[tt], rt[++t]=cnt++, 0, n-1);
	}
};

int qt[MAX];

void build(vector<int>& v) {
	int n = v.size();
	perseg::build(n);
	map<int, int> last;
	int at = 0;
	for (int i = 0; i < n; i++) {
		if (last.count(v[i])) {
			perseg::update(last[v[i]], -1);
			at++;
		}
		perseg::update(i, 1);
		qt[i] = ++at;
		last[v[i]] = i;
	}
}

int query(int l, int r) {
	return perseg::query(l, r, qt[r]);
}
