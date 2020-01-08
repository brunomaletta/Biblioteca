// SQRT Tree
//
// RMQ em O(1) com O(n log log n) pra buildar
// Funciona com qualquer operacao associativa
// Eh mais rapido que sparse table para n ~ 1e6
//
// build - O(n log log n)
// query - O(1)

namespace sqrtTree {
	int n, *v, prof, lim;
	vector<vector<int> > entre, pref, sulf, blk, getl;
	vector<int> sz, invsz;

	int op(int a, int b) { return min(a, b); }
	int ceillog(int x) { return __builtin_clz(0)-__builtin_clz(x)-1; }
	void build(int p, int l, int r) {
		if (p >= prof) return;
		int size = (int)sqrt(r-l+1), cnt = 0;
		if (sz[p]) size = (1<<sz[p]);
		else while (size - (size&-size)) size++;
		sz[p] = __builtin_popcount(size-1), invsz[sz[p]] = p;
		lim = max(lim, sz[p]);
		for (int i = l; i <= r; i++) getl[p][i] = l;
		for (int L = l; L <= r; L += size, cnt++) {
			int R = min(L+size-1, r);
			for (int i = L; i <= R; i++) blk[p][i] = cnt;
			pref[p][L] = v[L], sulf[p][R] = v[R];
			for (int i = L+1; i <= R; i++) pref[p][i] = op(pref[p][i-1], v[i]);
			for (int i = R-1; i >= L; i--) sulf[p][i] = op(sulf[p][i+1], v[i]);
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
		prof = ceillog(ceillog(n))+1;
		pref = sulf = blk = getl = vector<vector<int> >(prof, vector<int>(n));
		sz = invsz = vector<int>(2*ceillog(n)+1, 0);
		while (n2 - (n2&-n2)) n2++;
		entre = vector<vector<int> >(prof, vector<int>(n2+1));
		build(0, 0, n-1);
		for (int i = 1; i < lim; i++) if (!invsz[i]) invsz[i] = invsz[i-1];
	}
	int query(int l, int r) {
		if (l == r) return v[l];
		if (l+1 == r) return op(v[l], v[r]);
		int p = invsz[ceillog(l^r)];
		int ans = op(sulf[p][l], pref[p][r]);
		int a = blk[p][l]+1, b = blk[p][r]-1, L = getl[p][l];
		if (a <= b) ans = op(ans, entre[p][L+(a<<sz[p])+b]);
		return ans;
	}
}

