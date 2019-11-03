// Isomorfismo de Arvores
//
// Duas arvores T1 e T2 sao isomorfas
// sse T1.getHash() = T2.getHash()
//
// O(n log(n))

map<vector<int>, int> mapp;

struct tree {
	int n;
	vector<vector<int> > g;
	vector<int> subsize;

	tree(int n) {
		g.resize(n);
		subsize.resize(n);
	}
	void dfs(int k, int p=-1) {
		subsize[k] = 1;
		for (int i : g[k]) if (i != p) {
			dfs(i, k);
			subsize[k] += subsize[i];
		}
	}
	int centroid(int k, int p=-1, int size=-1) {
		if (size == -1) size = subsize[k];
		for (int i : g[k]) if (i != p)
			if (subsize[i] > size/2)
				return centroid(i, k, size);
		return k;
	}
	pair<int, int> centroids(int k=0) {
		dfs(k);
		int i = centroid(k), i2 = i;
		for (int j : g[i]) if (2*subsize[j] == subsize[k]) i2 = j;
		return {i, i2};
	}
	int hashh(int k, int p=-1) {
		vector<int> v;
		for (int i : g[k]) if (i != p) v.push_back(hashh(i, k));
		sort(v.begin(), v.end());
		if (!mapp.count(v)) mapp[v] = int(mapp.size());
		return mapp[v];
	}
	ll getHash(int k=0) {
		pair<int, int> c = centroids(k);
		ll a = hashh(c.first), b = hashh(c.second);
		if (a > b) swap(a, b);
		return (a<<30)+b;
	}
};
