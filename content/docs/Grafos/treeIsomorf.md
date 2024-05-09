---
weight: 10
title: "Isomorfismo de arvores"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 thash() retorna o hash da arvore (usando centroids como vertices especiais).

 Duas arvores sao isomorfas sse seu hash eh o mesmo



 O(|V|.log(|V|))



Link original: [treeIsomorf.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/treeIsomorf.cpp)

## Código
```cpp
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


// Versao mais rapida com hash, ideal para hash de floresta.
// subtree_hash(v, p) retorna o hash da subarvore enraizada em v com pai p.
// tree_hash() retorna o hash da arvore.
// forest_hash() retorna o hash da floresta.
// use o vetor forb[] para marcar vertices que nao podem ser visitados.
//
// O(|V|.log(|V|))

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int uniform(ll l, ll r) {
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

const int MOD = 1e9 + 7;
const int H = 13;
const int P = uniform(1, MOD-1);
const int P2 = uniform(1, MOD-1);

struct tree {
	int fn;
	vector<vector<int>> g;
	vector<int> sz, cs;
	vector<bool> forb;

	tree(int n_) : fn(n_), g(n_), sz(n_), forb(n_) {}

	void dfs_size(int v, int p) {
		sz[v] = 1;
		for (int u : g[v]) if (u != p and !forb[u]) {
			dfs_size(u, v), sz[v] += sz[u];
		}
	}
	void dfs_centroid(int v, int p, int n) {
		bool cent = true;
		for (int u : g[v]) if (u != p and !forb[u]) {
			dfs_centroid(u, v, n);
			if(sz[u] > n/2) cent = false;
		}
		if (cent and n - sz[v] <= n/2) cs.push_back(v);
	}
	int subtree_hash(int v, int p) {
		int h = H;
		for (int u : g[v]) if (u != p and !forb[u]) {
			h = ll(h) * (P + subtree_hash(u, v)) %  MOD;
		}
		return h;
	}
	int tree_hash(int v=0) {
		cs.clear();
		dfs_size(v, -1);
		dfs_centroid(v, -1, sz[v]);
		if (cs.size() == 1) return subtree_hash(cs[0], -1);
		assert (cs.size() == 2);
		int h1 = subtree_hash(cs[0], cs[1]);
		int h2 = subtree_hash(cs[1], cs[0]);
		return ll(P + h1) * (P + h2) % MOD;
	}
	int forest_hash() {
		fill(sz.begin(), sz.end(), 0);
		int hash = 1;
		for (int v = 0; v < fn; v++) if (!sz[v] and !forb[v]) {
			hash = hash * ll(P2 + tree_hash(v)) % MOD;
		}
		return hash;
	}
};
```
