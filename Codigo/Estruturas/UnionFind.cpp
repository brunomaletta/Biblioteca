// Union-Find com path compression e union by size
//
// Complexidades:
// build - O(n)
// find - O(1)
// une - O(1)

int n;
int v[MAX];    // v[i] : representante do conjunto que contem i
int size[MAX]; // size[i] : tamanho do conjunto que tem i como representante

void build() {
	for (int i = 0; i < n; i++) {
		v[i] = i;
		size[i] = 1;
	}
}

int find(int k) {
	return v[k] == k ? k : v[k] = find(v[k]);
}

void une(int a, int b) {
	a = find(a);
	b = find(b);
	if (size[a] > size[b]) swap(a, b);

	size[b] += size[a];
	v[a] = b;
}

// une sem union by size
//
// une e find ficam O(log(n))
//
// void une(int a, int b) {
// 	v[find(a)] = find(b);
// }
