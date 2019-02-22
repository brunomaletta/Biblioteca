// MergeSort Tree
//
// query(1, 0, n-1) retorna numero de
// elementos em [a, b] <= val
// Usa O(n log(n)) de memoria
//
// Complexidades:
// build - O(n log(n))
// query - O(log^2(n))

#define ALL(x) x.begin(),x.end()

int v[MAX];
vector<vector<int> > tree(4*MAX);
int n, a, b val;

void build(int p, int l, int r) {
	if (l == r) return tree[p].push_back(cr[l]);
	int m = (l+r)/2;
	build(2*p, l, m), build(2*p+1, m+1, r);
	merge(ALL(tree[2*p]), ALL(tree[2*p+1]), back_inserter(tree[p]));
}

int query(int p, int l, int r) {
	if (b < l or r < a) return 0; // to fora
	if (a <= l and r <= b) // to totalmente dentro
		return lower_bound(ALL(tree[p]), val+1) - tree[p].begin();
	int m = (l+r)/2;
	return query(2*p, l, m) + query(2*p+1, m+1, r);
}
