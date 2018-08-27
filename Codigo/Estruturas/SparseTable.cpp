// RMQ com sparse table
//
// MAX2 = log(MAX)
//
// Complexidades:
// build - O(n log(n))
// query - O(1)

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
