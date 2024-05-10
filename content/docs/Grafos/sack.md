---
weight: 10
title: "Sack (DSU em arvores)"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Responde queries de todas as sub-arvores

 offline



 O(n log(n))



Link original: [sack.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/sack.cpp)

## Código
```cpp
int sz[MAX], cor[MAX], cnt[MAX];
vector<int> g[MAX];
 
void build(int k, int d=0) {
	sz[k] = 1;
	for (auto& i : g[k]) {
		build(i, d+1); sz[k] += sz[i];
		if (sz[i] > sz[g[k][0]]) swap(i, g[k][0]);
	}
}
 
void compute(int k, int x, bool dont=1) {
	cnt[cor[k]] += x;
	for (int i = dont; i < g[k].size(); i++)
		compute(g[k][i], x, 0);
}
 
void solve(int k, bool keep=0) {
	for (int i = int(g[k].size())-1; i >= 0; i--)
		solve(g[k][i], !i);
	compute(k, 1);
	
	// agora cnt[i] tem quantas vezes a cor
	// i aparece na sub-arvore do k

	if (!keep) compute(k, -1, 0);
}
```
