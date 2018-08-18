// SQRT-decomposition para RMQ
//
// 0-indexed
// MAX2 = sqrt(MAX)
//
// O bloco da posicao x eh
// sempre x/q
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
	for (; a <= b and a % q; a++) ret = min(ret, v[a]);

	// bloco por bloco
	for (; a + q <= b; a += q) ret = min(ret, bl[a / q]);

	// linear no bloco de b
	for (; a <= b; a++) ret = min(ret, v[a]);

	return ret;
}
