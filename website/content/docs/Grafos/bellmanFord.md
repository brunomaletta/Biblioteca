---
weight: 10
title: "Bellman-Ford"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Calcula a menor distancia

 entre a e todos os vertices e

 detecta ciclo negativo

 Retorna 1 se ha ciclo negativo

 Nao precisa representar o grafo,

 soh armazenar as arestas



 O(nm)



Link original: [bellmanFord.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/bellmanFord.cpp)

## Código
```cpp
int n, m;
int d[MAX];
vector<pair<int, int>> ar; // vetor de arestas
vector<int> w;              // peso das arestas

bool bellman_ford(int a) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[a] = 0;

	for (int i = 0; i <= n; i++)
		for (int j = 0; j < m; j++) {
			if (d[ar[j].second] > d[ar[j].first] + w[j]) {
				if (i == n) return 1;

				d[ar[j].second] = d[ar[j].first] + w[j];
			}
		}

	return 0;
}
```
