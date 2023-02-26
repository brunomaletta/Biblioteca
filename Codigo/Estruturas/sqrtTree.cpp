// SQRT Tree
//
// RMQ em O(log log n) com O(n log log n) pra buildar
// Funciona com qualquer operacao associativa
// Tao rapido quanto a sparse table, mas usa menos memoria
// (log log (1e9) < 5, entao a query eh praticamente O(1))
//
// build - O(n log log n)
// query - O(log log n)

namespace sqrtTree {
	int n, *v;
	int pref[4][MAX], sulf[4][MAX], getl[4][MAX], entre[4][MAX], sz[4];

	int op(int a, int b) { return min(a, b); }
	inline int getblk(int p, int i) { return (i-getl[p][i])/sz[p]; }
	void build(int p, int l, int r) {
		if (l+1 >= r) return;
		for (int i = l; i <= r; i++) getl[p][i] = l;
		for (int L = l; L <= r; L += sz[p]) {
			int R = min(L+sz[p]-1, r);
			pref[p][L] = v[L], sulf[p][R] = v[R];
			for (int i = L+1; i <= R; i++) pref[p][i] = op(pref[p][i-1], v[i]);
			for (int i = R-1; i >= L; i--) sulf[p][i] = op(v[i], sulf[p][i+1]);
			build(p+1, L, R);
		}
		for (int i = 0; i <= sz[p]; i++) {
			int at = entre[p][l+i*sz[p]+i] = sulf[p][l+i*sz[p]];
			for (int j = i+1; j <= sz[p]; j++) entre[p][l+i*sz[p]+j] = at =
					op(at, sulf[p][l+j*sz[p]]);
		}
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		for (int p = 0; p < 4; p++) sz[p] = n2 = sqrt(n2);
		build(0, 0, n-1);
	}
	int query(int l, int r) {
		if (l+1 >= r) return l == r ? v[l] : op(v[l], v[r]);
		int p = 0;
		while (getblk(p, l) == getblk(p, r)) p++;
		int ans = sulf[p][l], a = getblk(p, l)+1, b = getblk(p, r)-1;
		if (a <= b) ans = op(ans, entre[p][getl[p][l]+a*sz[p]+b]);
		return op(ans, pref[p][r]);
	}
}
