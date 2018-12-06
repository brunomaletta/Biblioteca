// BIT de soma
//
// BIT 1-based, v 0-based
// Para mudar o valor da posicao p para x,
// faca: poe(x - query(p, p), p)
// l_bound(x) retorna o menor p tal que
// query(1, p+1) > x    (0 based!)
//
// Complexidades:
// build - O(n)
// poe - O(log(n))
// query - O(log(n))
// l_bound - O(log(n))

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
	for (; p <= n; p += p & -p) bit[p] += x;
}

// soma [1, p]
int pref(int p) {
	int ret = 0;
	for (; p; p -= p & -p) ret += bit[p];
	return ret;
}

// soma [a, b]
int query(int a, int b) {
	return query(b) - query(a - 1);
}

int l_bound(ll x) {
	int p = 0;
	for (int i = MAX2; i+1; i--) if (p + (1<<i) <= n
		and bit[p + (1<<i)] <= x) x -= bit[p += (1<<i)];
	return p;
}
