// Wavelet Tree
//
// Usa O(sigma + n log(sigma)) de memoria,
// onde sigma = MAXN - MINN
// query(i, j) retorna o numero de elementos de
// v[i, j) que pertencem a [x, y]
// kth(i, j, k) retorna o elemento que estaria
// na poscicao k de v[i, j), se ele fosse ordenado
//
// Complexidades:
// build - O(n log(sigma))
// query - O(log(sigma))
// kth   - O(log(sigma))

int n, v[MAX], x, y;
vector<vector<int> > esq(4*(MAXN-MINN));

void build(int b = 0, int e = n, int p = 1, int l = MINN, int r = MAXN) {
	if (l == r) return;
	int m = (l+r)/2; esq[p].push_back(0);
	for (int i = b; i < e; i++) esq[p].push_back(esq[p].back()+(v[i]<=m));

	int m2 = stable_partition(v+b, v+e, [=](int i){return i <= m;}) - v;
	build(b, m2, 2*p, l, m), build(m2, e, 2*p+1, m+1, r);
}

int query(int i, int j, int p = 1, int l = MINN, int r = MAXN) {
	if (y < l or r < x) return 0;
	if (x <= l and r <= y) return j-i;
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	return query(ei, ej, 2*p, l, m) + query(i-ei, j-ej, 2*p+1, m+1, r);
}

int kth(int i, int j, int k, int p=1, int l = MINN, int r = MAXN) {
	if (l == r) return l;
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	if (k <= ej-ei) return kth(ei, ej, k, 2*p, l, m);
	return kth(i-ei, j-ej, k-(ej-ei), 2*p+1, m+1, r);
}
