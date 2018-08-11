// RMQ com SQRT-decomposition, seg tree e sparse table
// Tudo 0-index

// Com SQRT-decomposition
//
// MAX2 = sqrt(MAX)
// 
// Complexidades:
// build - O(n)
// query - O(sqrt(n))

int n, q;
int v[MAX];
int bl[MAX2];

void build() {
	q = (int) sqrt(n);
  
  // computa cada bloco
	for (int i = 0; i <= q; i++) {
		bl[i] = INF;
		for (int j = 0; j < q and q * i + j < n; j++)
			bl[i] = min(bl[i], v[q * i + j]);
	}
}

int query(int a, int b) {
	int ret = INF;

	// linear no bloco de a
	while (a < b and a % q)
		ret = min(ret, v[a++]);

	// bloco por bloco
	while (a + q < b) {
		ret = min(ret, bl[a / q]);
		a += q;
	}

	// linear no bloco de b
	while (a <= b) ret = min(ret, v[a++]);

	return ret;
}

// Com seg tree
// 
// Complexidades:
// build - O(n)
// query - O(log(n))

int n;
int v[MAX];
int seg[4 * MAX];
int a, b;

int build(int p, int l, int r) {
	if (l == r) return seg[p] = v[l];

	int m = (l + r) / 2;

	return seg[p] = min(build(2 * p + 1, l, m),
			build(2 * p + 2, m + 1, r));
}

int query(int p, int l, int r) {
	if (l >= a and r <= b) return seg[p];
	if (r < a or l > b) return INF;

	int m = (l + r) / 2;

	return min(query(2 * p + 1, l, m),
			query(2 * p + 2, m + 1, r));
}

// Com sparse table
//
// MAX2 = log(MAX)
//
// Complexidades:
// build - O(n log(n))
// query(O(1))

int n;
int v[MAX];
int m[MAX][MAX2]; // m[i][j] : posicao do minimo
                  // em [v[i], v[i + 2^j - 1]]

void build() {
	for (int i = 0; i < n; i++) m[i][0] = i;

	for (int j = 1; 1 << j <= n; j++) {
		int tam = 1 << j;
		for (int i = 0; i + tam <= n; i++) {
			if (v[m[i][j - 1]] < v[m[i + tam/2][j - 1]])
				m[i][j] = m[i][j - 1];
			else m[i][j] = m[i + tam/2][j - 1];
		}
	}
}

int query(int a, int b) {
	int j = (int) log2(b - a + 1);

	return min(v[m[a][j]], v[m[b - (1 << j) + 1][j]]);
}
