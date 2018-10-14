// SegTree 2D Iterativa
//
// Consultas 0-based
// Um valor inicial em (x, y) deve ser colocado em seg[x+n][y+n]
// Query: soma do retangulo ((x1, y1), (x2, y2))
// Update: muda o valor da posicao (x, y) para val
//
// Complexidades:
// build - O(n^2)
// query - O(log^2(n))
// update - O(log^2(n))

int seg[2*MAX][2*MAX];
int n;

void build() {
	for (int x = n; x < 2*n; x++)
		for (int y = n - 1; y; y--)
			seg[x][y] = seg[x][2*y] + seg[x][2*y+1];

	for (int x = n - 1; x; x--) {
		for (int y = n; y < 2*n; y++)
			seg[x][y] = seg[2*x][y] + seg[2*x+1][y];

		for (int y = n - 1; y; y--)
			seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}

int query(int x1, int y1, int x2, int y2) {
	int ret = 0;
	int y1_ = y1 + n, y2_ = y2 + n;
	for (x1 += n, x2 += n; x1 <= x2; x1 /= 2, x2 /= 2) {
		if (x1 % 2 == 1) {
			y1 = y1_, y2 = y2_;
			for (; y1 <= y2; y1 /= 2, y2 /= 2) {
				if (y1 % 2 == 1) ret += seg[x1][y1++];
				if (y2 % 2 == 0) ret += seg[x1][y2--];
			}
			x1++;
		}
		if (x2 % 2 == 0) {
			y1 = y1_, y2 = y2_;
			for (; y1 <= y2; y1 /= 2, y2 /= 2) {
				if (y1 % 2 == 1) ret += seg[x2][y1++];
				if (y2 % 2 == 0) ret += seg[x2][y2--];
			}
			x2--;
		}
	}
	return ret;
}

void update(int x, int y, int val) {
	int y_ = y + n;
	for (x += n; x; x /= 2) {
		y = y_;
		if (x >= n) seg[x][y] += val;
		else seg[x][y] = seg[2*x][y] + seg[2*x+1][y];

		while (y /= 2) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}
