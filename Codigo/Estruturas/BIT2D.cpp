// BIT 2D de soma
//
// BIT 1-based
// Para mudar o valor da posicao (x, y) para k,
// faca: poe(x, y, k - sum(x, y, x, y))
//
// Complexidades:
// poe - O(log^2(n))
// query - O(log^2(n))

int n;
int bit[MAX][MAX];

void poe(int x, int y, int k) {
	for (int y2 = y; x <= n; x += x & -x)
		for (y = y2; y <= n; y += y & -y)
			bit[x][y] += k;
}

int sum(int x, int y) {
	int ret = 0;
	for (int y2 = y; x; x -= x & -x)
		for (y = y2; y; y -= y & -y)
			ret += bit[x][y];

	return ret;
}

int query(int x, int y, int z, int w) {
	return sum(z, w) - sum(x-1, w)
		- sum(z, y-1) + sum(x-1, y-1);
}
