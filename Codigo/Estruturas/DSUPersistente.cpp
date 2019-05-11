// Union-Find Persistente
//
// Complexidades:
// build - O(n)
// find - O(log(n))
// une - O(log(n))

int n, p[MAX], sz[MAX], ti[MAX];

void build() {
	for (int i = 0; i < n; i++) {
		p[i] = i;
		sz[i] = 1;
		ti[i] = -INF;
	}
}

int find(int k, int t) {
	if (p[k] == k or ti[k] > t) return k;
	return find(p[k], t);
}

void une(int a, int b, int t) {
	a = find(a); b = find(b);
	if (a == b) return;
	if (sz[a] > sz[b]) swap(a, b);

	sz[b] += sz[a];
	p[a] = b;
	ti[a] = t;
}
