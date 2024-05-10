---
weight: 10
title: "Johnson"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 funciona igual ao Floyd-Warshall

 encontra o menor caminho entre todo

 par de vertices e retorna 1 sse tem 

 ciclo negativo no grafo

 

 O(nm log(m))



Link original: [johnson.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/johnson.cpp)

## Código
```cpp
vector<pair<int, ll>> g[MAX]; // {vizinho, peso}
ll d[MAX][MAX];

bool johnson(int n) {
	vector<ll> h(n, 0);
	for (int i = 0; i <= n; i++)
		for (int v = 0; v < n; v++)
			for (auto [u, w] : g[v]) if (h[u] > h[v] + w) {
				if (i == n) return 1;
				h[u] = h[v] + w;
			}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) d[i][j] = LINF;
		d[i][i] = 0;
		priority_queue<pair<ll, int>> pq;
		pq.emplace(0, i);
		while (pq.size()) {
			auto [ndist, v] = pq.top(); pq.pop();
			if (-ndist > d[i][v]) continue;

			for (auto [u, w] : g[v]) {
				w += h[v] - h[u];
				if (d[i][u] > d[i][v] + w) {
					d[i][u] = d[i][v] + w;
					pq.emplace(-d[i][u], u);
				}
			}
		}
		for (int j = 0; j < n; j++)
			d[i][j] += h[j] - h[i];
	}

	return 0;
}
```
