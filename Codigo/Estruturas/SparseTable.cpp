// Sparse Table
//
// Resolve RMQ
// MAX2 = log(MAX)
//
// Complexidades:
// build - O(n log(n))
// query - O(1)

int n;
int v[MAX];
int m[MAX][MAX2]; // m[i][j] : minimo de v[i, i + 2^j - 1]

void build() {
	for (int i = 0; i < n; i++) m[i][0] = v[i];
	for (int j=1; 1 << j <= n; j++) for (int i=0; i+(1<<j) <= n; i++)
		m[i][j] = min(m[i][j-1], m[i+(1<<(j-1))][j-1]);
}

int query(int a, int b) {
	int j = __builtin_clz(0) - __builtin_clz(b-a+1) - 1;
	return min(m[a][j], m[b-(1<<j)+1][j]);
}
