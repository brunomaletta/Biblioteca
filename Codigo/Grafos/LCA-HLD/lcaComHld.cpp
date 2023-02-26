// LCA com HLD
//
// Assume que um vertice eh ancestral dele mesmo, ou seja,
// se a eh ancestral de b, lca(a, b) = a
// Para buildar pasta chamar build(root)
// anc(a, b) responde se 'a' eh ancestral de 'b'
//
// Complexidades:
// build - O(n)
// lca - O(log(n))
// anc - O(1)

vector<int> g[MAX];
int pos[MAX], h[MAX], sz[MAX];
int pai[MAX], t;

void build(int k, int p = -1, int f = 1) {
	pos[k] = t++; sz[k] = 1;
	for (int& i : g[k]) if (i != p) {
		pai[i] = k;
		h[i] = (i == g[k][0] ? h[k] : i);
		build(i, k, f); sz[k] += sz[i];
		
		if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
	}
	if (p*f == -1) t = 0, h[k] = k, build(k, -1, 0);
}

int lca(int a, int b) {
	if (pos[a] < pos[b]) swap(a, b);
	return h[a] == h[b] ? b : lca(pai[h[a]], b);
}

bool anc(int a, int b) {
	return pos[a] <= pos[b] and pos[b] <= pos[a]+sz[a]-1;
}

