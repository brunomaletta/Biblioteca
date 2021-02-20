// Centroid
//
// Computa os 2 centroids da arvore
//
// O(n)

int n, subsize[MAX];
vector<int> g[MAX];

void dfs(int k, int p=-1) {
	subsize[k] = 1;
	for (int i : g[k]) if (i != p) {
		dfs(i, k);
		subsize[k] += subsize[i];
	}
}

int centroid(int k, int p=-1, int size=-1) {
	if (size == -1) size = subsize[k];
	for (int i : g[k]) if (i != p) if (subsize[i] > size/2)
		return centroid(i, k, size);
	return k;
}

pair<int, int> centroids(int k=0) {
	dfs(k);
	int i = centroid(k), i2 = i;
	for (int j : g[i]) if (2*subsize[j] == subsize[k]) i2 = j;
	return {i, i2};
}
