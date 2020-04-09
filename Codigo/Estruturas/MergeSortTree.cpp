// MergeSort Tree
//
// query(a, b, val) retorna numero de
// elementos em [a, b] <= val
// Usa O(n log(n)) de memoria
//
// Complexidades:
// build - O(n log(n))
// query - O(log^2(n))

#define ALL(x) x.begin(),x.end()

int v[MAX], n;
vector<int> tree[4*MAX];

void build(int p, int l, int r) {
	if (l == r) return tree[p].push_back(v[l]);
	int m = (l+r)/2;
	build(2*p, l, m), build(2*p+1, m+1, r);
	merge(ALL(tree[2*p]), ALL(tree[2*p+1]), back_inserter(tree[p]));
}

int query(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	if (b < l or r < a) return 0; // to fora
	if (a <= l and r <= b) // to totalmente dentro
		return lower_bound(ALL(tree[p]), val+1) - tree[p].begin();
	int m = (l+r)/2;
	return query(a, b, val, 2*p, l, m) + query(a, b, val, 2*p+1, m+1, r);
}
