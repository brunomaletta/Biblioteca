// Isomorfismo de arvores
// 
// thash() retorna o hash da arvore (usando centroids como vertices especiais).
// Duas arvores sao isomorfas sse seu hash eh o mesmo
//
// O(|V|.log(|V|))

map<vector<int>, int> mphash;

struct tree {
	int n;
	vector<vector<int>> g;
	vector<int> sz, cs;

	tree(int n_) : n(n_), g(n_), sz(n_) {}

	void dfs_centroid(int v, int p) {
		sz[v] = 1;
		bool cent = true;
		for (int u : g[v]) if (u != p) {
			dfs_centroid(u, v), sz[v] += sz[u];
			if(sz[u] > n/2) cent = false;
		}
		if (cent and n - sz[v] <= n/2) cs.push_back(v);
	}
	int fhash(int v, int p) {
		vector<int> h;
		for (int u : g[v]) if (u != p) h.push_back(fhash(u, v));
		sort(h.begin(), h.end());
		if (!mphash.count(h)) mphash[h] = mphash.size();
		return mphash[h];
	}
	ll thash() {
		cs.clear();
		dfs_centroid(0, -1);
		if (cs.size() == 1) return fhash(cs[0], -1);
		ll h1 = fhash(cs[0], cs[1]), h2 = fhash(cs[1], cs[0]);
		return (min(h1, h2) << 30) + max(h1, h2);
	}
};
