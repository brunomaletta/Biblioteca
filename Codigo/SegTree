// SegTree com Lazy Propagation
// by BM
//
// SegTree 1-based, vetor 0-based
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

int seg[4 * MAX];
int lazy[4 * MAX];
int v[MAX];
int n, a, b, x;

int build(int p, int l, int r) {
	lazy[p] = 0;
	if (l == r) return seg[p] = v[l - 1];

	int m = (l + r) / 2;
	return seg[p] = build(2 * p, l, m) + build(2 * p + 1, m + 1, r);
}

// propagar o que ta em p para os filhos
void prop(int p, int l, int r) {
	// soma o lazy
	seg[p] += lazy[p] * (r - l + 1);

	// propaga pros filhos
	if (l != r) {
		lazy[2 * p] += lazy[p];
		lazy[2 * p + 1] += lazy[p];
	}

	// zera o lazy
	lazy[p] = 0;
}

// somar x no intervalo [l, r]
int lazy_op(int p, int l, int r) {
	// soma x * (tamanho do intervalo)
	seg[p] += x * (r - l + 1);

	// suja os filhos
	if (l != r) {
		lazy[2 * p] += x;
		lazy[2 * p + 1] += x;
	}

	return seg[p];
}

int query(int p, int l, int r) {
	// propaga
	prop(p, l, r);

	// to totalmente dentro
	if (l >= a and r <= b) return seg[p];
	// to fora
	if (r < a or l > b) return 0;

	int m = (l + r) / 2;
	return query(2 * p, l, m) + query(2 * p + 1, m + 1, r);
}

int update(int p, int l, int r) {
	// propaga
	prop(p, l, r);

	// to totalmente dentro
	if (l >= a and r <= b) return lazy_op(p, l, r);
	// to fora
	if (r < a or l > b) return seg[p];

	int m = (l + r) / 2;
	return seg[p] = update(2 * p, l, m) + update(2 * p + 1, m + 1, r);
}
