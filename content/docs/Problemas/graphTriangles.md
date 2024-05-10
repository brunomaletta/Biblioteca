---
weight: 10
title: "Triangulos em Grafos"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 get_triangles(i) encontra todos os triangulos ijk no grafo

 Custo nas arestas

 retorna {custo do triangulo, {j, k}}



 O(m sqrt(m) log(n)) se chamar para todos os vertices



Link original: [graphTriangles.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/graphTriangles.cpp)

## Código
```cpp
vector<pair<int, int>> g[MAX]; // {para, peso}

#warning o 'g' deve estar ordenado
vector<pair<int, pair<int, int>>> get_triangles(int i) {
	vector<pair<int, pair<int, int>>> tri;
	for (pair<int, int> j : g[i]) {
		int a = i, b = j.first;
		if (g[a].size() > g[b].size()) swap(a, b);
		for (pair<int, int> c : g[a]) if (c.first != b and c.first > j.first) {
			auto it = lower_bound(g[b].begin(), g[b].end(), make_pair(c.first, -INF));
			if (it == g[b].end() or it->first != c.first) continue;
			tri.push_back({j.second+c.second+it->second, {a == i ? b : a, c.first}});
		}
	}
	return tri;
}
```
