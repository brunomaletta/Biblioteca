// Sparse Table Disjunta
//
// Resolve qualquer operacao associativa
// MAX2 = log(MAX)
//
// Complexidades:
// build - O(n log(n))
// query - O(1)

namespace sparse {
	int m[MAX2][2*MAX], n, v[2*MAX];
	int op(int a, int b) { return min(a, b); }
	void build(int n2, int* v2) {
		n = n2;
		for (int i = 0; i < n; i++) v[i] = v2[i];
		while (n&(n-1)) n++;
		for (int j = 0; (1<<j) < n; j++) {
			int len = 1<<j;
			for (int c = len; c < n; c += 2*len) {
				m[j][c] = v[c], m[j][c-1] = v[c-1];
				for (int i = c+1; i <  c+len; i++) m[j][i] = op(m[j][i-1], v[i]);
				for (int i = c-2; i >= c-len; i--) m[j][i] = op(v[i], m[j][i+1]);
			}
		}
	}
	int query(int l, int r) {
		if (l == r) return v[l];
		int j = __builtin_clz(1) - __builtin_clz(l^r);
		return op(m[j][l], m[j][r]);
	}
}
