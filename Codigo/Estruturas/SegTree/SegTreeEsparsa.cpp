// SegTree Esparca
//
// Query: soma do range [a, b]
// Update: flipa os valores de [a, b]
//
// Complexidades:
// build - O(n)
// query - O(log^2(n))
// update - O(log^2(n))
// porem muito ruim da pra fazer O(logn)

typedef long long ll;

namespace seg {
	unordered_map<ll, int> t, lazy;

	void build() { t.clear(), lazy.clear(); }

	void prop(ll p, int l, int r) {
		if (!lazy[p]) return;
		t[p] = r-l+1-t[p];
		if (l != r) lazy[2*p]^=lazy[p], lazy[2*p+1]^=lazy[p];
		lazy[p] = 0;
	}

	int query(int a, int b, ll p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return t[p];

		int m = l+r>>1;
		return query(a, b, 2*p, l, m)+query(a, b, 2*p+1, m+1, r);
	}

	int update(int a, int b, ll p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return t[p];
		if (a <= l and r <= b) {
			lazy[p] ^= 1;
			prop(p, l, r);
			return t[p];
		}
		int m = l+r>>1;
		return t[p] = update(a, b, 2*p, l, m)+update(a, b, 2*p+1, m+1, r);
	}
};
