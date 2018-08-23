// BIT de soma
//
// BIT 1-based, v 0-based
// Para mudar o valor da posicao p para x,
// faca: poe(x - sum(p, p), p)
//
// Complexidades:
// build - O(n)
// poe - O(log(n))
// query - O(log(n))

int n;
int bit[MAX];
int v[MAX];

void build() {
	bit[0] = 0;
	for (int i = 1; i <= n; i++) bit[i] = v[i - 1];

	for (int i = 1; i <= n; i++) {
		int j = i + (i & -i);
		if (j <= n) bit[j] += bit[i];
	}
}

// soma x na posicao p
void poe(int x, int p) {
	while (p <= n) {
		bit[p] += x;
		p += p & -p;
	}
}

// soma [1, p]
int query(int p) {
	int ret = 0;
	while (p) {
		ret += bit[p];
		p -= p & -p;
	}
	return ret;
}

// soma [a, b]
int sum(int a, int b) {
	return query(b) - query(a - 1);
}
