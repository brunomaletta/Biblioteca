// Centroid decomposition
//
// O(n log(n))

int n;
vvi g(MAX);
int subsize[MAX];
int rem[MAX];
int pai[MAX];

void dfs(int k, int last) {
	subsize[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (g[k][i] != last and !rem[g[k][i]]) {
			dfs(g[k][i], k);
			subsize[k] += subsize[g[k][i]];
		}
}

int centroid(int k, int last, int size) {
	for (int i = 0; i < (int) g[k].size(); i++) {
		int u = g[k][i];
		if (rem[u] or u == last) continue;
		if (subsize[u] > size / 2)
			return centroid(u, k, size);
	}
	// k eh o centroid
	return k;
}

void decomp(int k, int last) {
	dfs(k, k);

	// acha e tira o centroid
	int c = centroid(k, k, subsize[k]);
	rem[c] = 1;
	pai[c] = last;
	if (k == last) pai[c] = c;

	// decompoe as sub-arvores
	for (int i = 0; i < (int) g[c].size(); i++)
		if (!rem[g[c][i]]) decomp(g[c][i], c);
}

void build() {
	memset(rem, 0, sizeof rem);
	decomp(0, 0);
}
