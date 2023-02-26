// Distinct Range Query com Update
//
// build - O(n log(n))
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

namespace bit {
	ord_set<pair<int, int>> bit[MAX];

	void build() {
		for (int i = 1; i <= n; i++) bit[i].insert({nxt[i-1], i-1});
		for (int i = 1; i <= n; i++) {
			int j = i + (i&-i);
			if (j <= n) for (auto x : bit[i]) bit[j].insert(x);
		}
	}
	int pref(int p, int x) {
		int ret = 0;
		for (; p; p -= p&-p) ret += bit[p].order_of_key({x, -INF});
		return ret;
	}
	int query(int l, int r, int x) {
		return pref(r+1, x) - pref(l, x);
	}
	void update(int p, int x) {
		int p2 = p;
		for (p++; p <= n; p += p&-p) {
			bit[p].erase({nxt[p2], p2});
			bit[p].insert({x, p2});
		}
	}
}

void build() {
	for (int i = 0; i < n; i++) nxt[i] = INF;
	for (int i = 0; i < n; i++) prv[i] = -INF;
	vector<pair<int, int>> t;
	for (int i = 0; i < n; i++) t.push_back({v[i], i});
	sort(t.begin(), t.end());
	for (int i = 0; i < n; i++) {
		if (i and t[i].first == t[i-1].first)
			prv[t[i].second] = t[i-1].second;
		if (i+1 < n and t[i].first == t[i+1].first)
			nxt[t[i].second] = t[i+1].second;
	}

	for (int i = 0; i < n; i++) ocor[v[i]].insert(i);

	bit::build();
}

void muda(int p, int x) {
	bit::update(p, x);
	nxt[p] = x;
}

int query(int a, int b) {
	return b-a+1 - bit::query(a, b, b+1);
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

