// DSU
//
// Une dois conjuntos e acha a qual conjunto um elemento pertence por seu id
//
// dsu_build: O(n)
// find e unite: O(a(n)) ~= O(1) amortizado

int id[MAX], sz[MAX];

void dsu_build(int n) { for(int i=0; i<n; i++) sz[i] = 1, id[i] = i; }

int find(int a) { return id[a] = a == id[a] ? a : find(id[a]); }

void unite(int a, int b) {
	a = find(a), b = find(b);
	if(sz[a] < sz[b]) swap(a,b);

	sz[a] += sz[b];
	id[b] = a;
}
