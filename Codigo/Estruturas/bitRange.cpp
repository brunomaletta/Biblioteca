// BIT com update em range
//
// Operacoes 0-based
// query(l, r) retorna a soma de v[l..r]
// update(l, r, x) soma x em v[l..r]
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

namespace bit {
	ll bit[2][MAX+2];
	int n;

	void build(int n2, int* v) {
		n = n2;
		for (int i = 1; i <= n; i++)
			bit[1][min(n+1, i+(i&-i))] += bit[1][i] += v[i-1];
	}
	ll get(int x, int i) {
		ll ret = 0;
		for (; i; i -= i&-i) ret += bit[x][i];
		return ret;
	}
	void add(int x, int i, ll val) {
		for (; i <= n; i += i&-i) bit[x][i] += val;
	}
	ll get2(int p) {
		return get(0, p) * p + get(1, p);
	}
	ll query(int l, int r) {
		return get2(r+1) - get2(l);
	}
	void update(int l, int r, ll x) {
		add(0, l+1, x), add(0, r+2, -x);
		add(1, l+1, -x*l), add(1, r+2, x*(r+1));
	}
};
