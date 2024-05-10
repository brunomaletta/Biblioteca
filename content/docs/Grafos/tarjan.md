---
weight: 10
title: "Tarjan para SCC"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 O(n + m)



Link original: [tarjan.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/tarjan.cpp)

## Código
```cpp
vector<int> g[MAX];
stack<int> s;
int vis[MAX], comp[MAX];
int id[MAX];

// se quiser comprimir ciclo ou achar ponte em grafo nao direcionado,
// colocar um if na dfs para nao voltar pro pai da DFS tree
int dfs(int i, int& t) {
	int lo = id[i] = t++;
	s.push(i);
	vis[i] = 2;

	for (int j : g[i]) {
		if (!vis[j]) lo = min(lo, dfs(j, t));
		else if (vis[j] == 2) lo = min(lo, id[j]);
	}

	// aresta de i pro pai eh uma ponte (no caso nao direcionado)
	if (lo == id[i]) while (1) {
		int u = s.top(); s.pop();
		vis[u] = 1, comp[u] = i;
		if (u == i) break;
	}

	return lo;
}

void tarjan(int n) {
	int t = 0;
	for (int i = 0; i < n; i++) vis[i] = 0;

	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i, t);
}
```
