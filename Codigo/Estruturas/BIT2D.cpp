// BIT 2D de soma
//
// BIT 1-based
// Para mudar o valor da posicao (x, y) para k,
// faça: poe(x, y, k - sum(x, y, x, y))
//
// Complexidades:
// build - O(n^2 log^2(n))
// poe - O(log^2(n))
// query - O(log^2(n))

int n;
int bit[MAX][MAX];
int M[MAX][MAX];

void poe(int x, int y, int k) {
	int y2 = y;
	while (x <= n) {
		y = y2;
		while (y <= n) {
			bit[x][y] += k;
			y += y & -y;
		}
		x += x & -x;
	}
}

int query(int x, int y) {
	int ret = 0;
	int y2 = y;
	while (x) {
		y = y2;
		while (y) {
			ret += bit[x][y];
			y -= y & -y;
		}
		x -= x & -x;
	}
	return ret;
}

int sum(int x, int y, int z, int w) {
	int ret = query(z, w);
	if (x > 1) ret -= query(x - 1, w);
	if (y > 1) ret -= query(z, y - 1);
	if (x > 1 and y > 1) ret += query(x - 1, y - 1);

	return ret;
}

void build() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			bit[i][j] = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			poe(i, j, M[i - 1][j - 1]);
}
