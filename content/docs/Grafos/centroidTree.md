---
weight: 10
title: "Centroid Tree"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Constroi a centroid tree

 p[i] eh o pai de i na centroid-tree

 dist[i][k] = distancia na arvore original entre i

 e o k-esimo ancestral na arvore da centroid



 O(n log(n)) de tempo e memoria



Link original: [centroidTree.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/centroidTree.cpp)

## Código
```cpp
vector<int> g[MAX], dist[MAX];
int sz[MAX], rem[MAX], p[MAX];

int dfs_sz(int i, int l=-1) {
	sz[i] = 1;
	for (int j : g[i]) if (j != l and !rem[j]) sz[i] += dfs_sz(j, i);
	return sz[i];
}

int centroid(int i, int l, int size) {
	for (int j : g[i]) if (j != l and !rem[j] and sz[j] > size / 2)
		return centroid(j, i, size);
	return i;
}

void dfs_dist(int i, int l, int d=0) {
	dist[i].push_back(d);
	for (int j : g[i]) if (j != l and !rem[j])
		dfs_dist(j, i, d+1);
}

void decomp(int i, int l = -1) {
	int c = centroid(i, i, dfs_sz(i));
	rem[c] = 1, p[c] = l;
	dfs_dist(c, c);
	for (int j : g[c]) if (!rem[j]) decomp(j, c);
}

void build(int n) {
	for (int i = 0; i < n; i++) rem[i] = 0, dist[i].clear();
	decomp(0);
	for (int i = 0; i < n; i++) reverse(dist[i].begin(), dist[i].end());
}
```
