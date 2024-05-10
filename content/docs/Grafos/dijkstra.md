---
weight: 10
title: "Dijkstra"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 encontra menor distancia de x

 para todos os vertices

 se ao final do algoritmo d[i] = LINF,

 entao x nao alcanca i



 O(m log(n))



Link original: [dijkstra.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/dijkstra.cpp)

## Código
```cpp
ll d[MAX];
vector<pair<int, int>> g[MAX]; // {vizinho, peso}

int n;
 
void dijkstra(int v) {
	for (int i = 0; i < n; i++) d[i] = LINF;
	d[v] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.emplace(0, v);
 
	while (pq.size()) {
		auto [ndist, u] = pq.top(); pq.pop();
		if (-ndist > d[u]) continue;
 
		for (auto [idx, w] : g[u]) if (d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.emplace(-d[idx], idx);
		}
	}
}
```
