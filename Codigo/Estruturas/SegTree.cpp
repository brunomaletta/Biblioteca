// SegTree recursiva com Lazy Propagation
//
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

int seg[4*MAX];
int lazy[4*MAX];
int v[MAX];
int n, a, b, x;

int build(int p, int l, int r) {
	lazy[p] = 0;
	if (l == r) return seg[p] = v[l];

	int m = (l+r)/2;
	return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
}

void prop(int p, int l, int r) {
	seg[p] += lazy[p] * (r-l+1);
	if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
	lazy[p] = 0;
}

int query(int p, int l, int r) {
	prop(p, l, r);
	if (a <= l and r <= b) return seg[p];
	if (b < l or r < a) return 0;

	int m = (l+r)/2;
	return query(2*p, l, m) + query(2*p+1, m+1, r);
}

int update(int p, int l, int r) {
	prop(p, l, r);
	if (a <= l and r <= b) {
		if (l != r) lazy[2*p] += x, lazy[2*p+1] += x;
		return seg[p] += x * (r-l+1);
	}
	if (b < l or r < a) return seg[p];

	int m = (l+r)/2;
	return seg[p] = update(2*p, l, m) + update(2*p+1, m+1, r);
}
