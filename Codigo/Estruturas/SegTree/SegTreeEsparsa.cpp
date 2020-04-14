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

namespace seg {
	int t[MAX], lazy[MAX];
	int L[MAX], R[MAX];
	int ptr = 2;
	int get_l(int i){
		if (L[i] == 0)
			L[i] = ptr++;
		return L[i];
	}
	int get_r(int i){
		if (R[i] == 0)
			R[i] = ptr++;
		return R[i];
	}

	void build() { ptr = 2; }

	void prop(int p, int l, int r) {
		if (!lazy[p]) return;
		t[p] = r-l+1-t[p];
		if (l != r) lazy[get_l(p)]^=lazy[p], lazy[get_r(p)]^=lazy[p];
		lazy[p] = 0;
	}

	int query(int a, int b, int p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return t[p];

		int m = (l+r)>>1;
		return query(a, b, get_l(p), l, m)+query(a, b, get_r(p), m+1, r);
	}

	int update(int a, int b, int p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return t[p];
		if (a <= l and r <= b) {
			lazy[p] ^= 1;
			prop(p, l, r);
			return t[p];
		}
		int m = (l+r)>>1;
		return t[p] = update(a, b, get_l(p), l, m)+update(a, b, get_r(p), m+1, r);
	}
};
