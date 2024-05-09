---
weight: 10
title: "Kruskal"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Gera e retorna uma AGM e seu custo total a partir do vetor de arestas (edg)

 do grafo



 O(m log(m) + m a(m))

 864875



Link original: [kruskal.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/kruskal.cpp)

## Código
```cpp
vector<tuple<int, int, int>> edg; // {peso,[x,y]}

// DSU em O(a(n))
void dsu_build();
int find(int a);
void unite(int a, int b);

pair<ll, vector<tuple<int, int, int>>> kruskal(int n) {
	dsu_build(n);
	sort(edg.begin(), edg.end());
	
	ll cost = 0;
	vector<tuple<int, int, int>> mst;
	for (auto [w,x,y] : edg) if (find(x) != find(y)) {
		mst.emplace_back(w, x, y);
		cost += w;
		unite(x,y);
	}
	return {cost, mst};
}
```
