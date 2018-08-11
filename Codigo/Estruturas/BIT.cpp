// BIT de soma
//
// BIT 1-based
// Para mudar o valor da posicao p para x,
// faça: poe(x - sum(p, p), p)
//
// Complexidades:
// build - O(n log(n))
// poe - O(log(n))
// query - O(log(n))

int n;
int bit[MAX];
int v[MAX];

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
	while (p > 0) {
		ret += bit[p];
		p -= p & -p;
	}
	return ret;
}

// soma [a, b]
int sum(int a, int b) {
	if (a == 1) return query(b);
	return query(b) - query(a - 1);
}

void build() {
	for (int i = 1; i <= n; i++) bit[i] = 0;

	for (int i = 1; i <= n; i++) poe(v[i - 1], i);
}
