// SQRT Tree
//
// RMQ em O(log log n) com O(n log log n) pra buildar
// Funciona com qualquer operacao associativa
// 2x mais rapido pra 1e5 e 7x mais rapido pra 1e6
// (comparando o tempo de buildar com sparse table)
// (log log (1e9) < 5, entao a query eh praticamente O(1))
//
// build - O(n log log n)
// query - O(log log n)

namespace sqrtTree {
	int n, *v;
	int pref[4][MAX], sulf[4][MAX], blk[4][MAX], getl[4][MAX];
	int sz[4], entre[4][MAX];

	int op(int a, int b) { return min(a, b); }
	void build(int p, int l, int r) {
		if (l+1 >= r) return;
		for (int L = l, cnt = 0; L <= r; L += sz[p], cnt++) {
			int R = min(L+sz[p]-1, r);
			for (int i = L; i <= R; i++) blk[p][i] = cnt, getl[p][i] = l;
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
		while (blk[p][l] == blk[p][r]) p++;
		int ans = sulf[p][l], a = blk[p][l]+1, b = blk[p][r]-1;
		if (a <= b) ans = op(ans, entre[p][getl[p][l]+a*sz[p]+b]);
		return op(ans, pref[p][r]);
	}
}
