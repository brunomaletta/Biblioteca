// Distinct Range Query com Update
//
// build - O(n log^2(n))
// query - O(log^2(n))
// update - O(log^2(n))

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

int v[MAX], n, nxt[MAX], prv[MAX];
map<int, set<int> > ocor;

namespace seg {
	ord_set<ii> seg[4*MAX];

	void build(int p=1, int l=0, int r=n-1) {
		if (l == r) return (void)seg[p].insert({nxt[l], l});
		int m = (l+r)/2;
		build(2*p, l, m), build(2*p+1, m+1, r);
		for (ii i : seg[2*p]) seg[p].insert(i);
		for (ii i : seg[2*p+1]) seg[p].insert(i);
	}
	int query(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p].order_of_key({x, -INF});
		int m = (l+r)/2;
		return query(a, b, x, 2*p, l, m)+query(a, b, x, 2*p+1, m+1, r);
	}
	void update(int a, int x, int p=1, int l=0, int r=n-1) {
		if (a < l or r < a) return;
		seg[p].erase({nxt[a], a});
		seg[p].insert({x, a});
		if (l == r) return;
		int m = (l+r)/2;
		update(a, x, 2*p, l, m), update(a, x, 2*p+1, m+1, r);
	}
}

void build() {
	for (int i = 0; i < n; i++) nxt[i] = INF;
	for (int i = 0; i < n; i++) prv[i] = -INF;
	vector<ii> t;
	for (int i = 0; i < n; i++) t.push_back({v[i], i});
	sort(t.begin(), t.end());
	for (int i = 0; i < n; i++) {
		if (i and t[i].f == t[i-1].f) prv[t[i].s] = t[i-1].s;
		if (i+1 < n and t[i].f == t[i+1].f) nxt[t[i].s] = t[i+1].s;
	}

	for (int i = 0; i < n; i++) ocor[v[i]].insert(i);

	seg::build();
}

void muda(int p, int x) {
	seg::update(p, x);
	nxt[p] = x;
}

int query(int a, int b) {
	return b-a+1 - seg::query(a, b, b+1);
}

void update(int p, int x) { // mudar valor na pos. p para x
	if (prv[p] > -INF) muda(prv[p], nxt[p]);
	if (nxt[p] < INF) prv[nxt[p]] = prv[p];

	ocor[v[p]].erase(p);
	if (!ocor[x].size()) {
		muda(p, INF);
		prv[p] = -INF;
	} else if (*ocor[x].rbegin() < p) {
		int i = *ocor[x].rbegin();
		prv[p] = i;
		muda(p, INF);
		muda(i, p);
	} else {
		int i = *ocor[x].lower_bound(p);
		if (prv[i] > -INF) {
			muda(prv[i], p);
			prv[p] = prv[i];
		} else prv[p] = -INF;
		prv[i] = p;
		muda(p, i);
	}
	v[p] = x; ocor[x].insert(p);
}
