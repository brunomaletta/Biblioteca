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
