// SQRT Tree
//
// RMQ em O(1) com O(n log log n) pra buildar
// Funciona com qualquer operacao associativa
// 2x mais rapido pra 1e5 e 5x mais rapido pra 1e6
// (comparando o tempo de buildar com sparse table)
//
// build - O(n log log n)
// query - O(1)

namespace sqrtTree {
	int n, *v;
	int pref[6][MAX], sulf[6][MAX], blk[6][MAX], getl[6][MAX];
	int sz[30], invsz[30], entre[6][MAX];

	int op(int a, int b) { return min(a, b); }
	void build(int p, int l, int r) {
		if (l+1 >= r) return;
		int size = 1<<sz[p], cnt = 0;
		for (int L = l; L <= r; L += size, cnt++) {
			int R = min(L+size-1, r);
			for (int i = L; i <= R; i++) blk[p][i] = cnt, getl[p][i] = l;
			pref[p][L] = v[L], sulf[p][R] = v[R];
			for (int i = L+1; i <= R; i++) pref[p][i] = op(pref[p][i-1], v[i]);
			for (int i = R-1; i >= L; i--) sulf[p][i] = op(v[i], sulf[p][i+1]);
			build(p+1, L, R);
		}
		for (int i = 0; i < cnt; i++) {
			int at = entre[p][l+(i<<sz[p])+i] = sulf[p][l+(i<<sz[p])];
			for (int j = i+1; j < cnt; j++) entre[p][l+(i<<sz[p])+j] = at =
				op(at, sulf[p][l+(j<<sz[p])]);
		}
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		memset(invsz, 0, sizeof(invsz));
		for (int p = 0; p < 6; p++) {
			n2 = sqrt(n2);
			while (n2-(n2&-n2)) n2++;
			sz[p] = __builtin_popcount(n2-1), invsz[sz[p]] = p;
		}
		for (int i = 1; i < sz[0]; i++) if (!invsz[i]) invsz[i] = invsz[i-1];
		build(0, 0, n-1);
	}
	int query(int l, int r) {
		if (l+1 >= r) return l == r ? v[l] : op(v[l], v[r]);
		int p = invsz[__builtin_clz(0)-__builtin_clz(l^r)-1];
		int ans = sulf[p][l];
		int a = blk[p][l]+1, b = blk[p][r]-1, L = getl[p][l];
		if (a <= b) ans = op(ans, entre[p][L+(a<<sz[p])+b]);
		return op(ans, pref[p][r]);
	}
}
