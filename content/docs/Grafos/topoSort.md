---
weight: 10
title: "Topological Sort"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Retorna uma ordenacaoo topologica de g

 Se g nao for DAG retorna um vetor vazio



 O(n + m)



Link original: [topoSort.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/topoSort.cpp)

## Código
```cpp
vector<int> g[MAX];

vector<int> topo_sort(int n) {
	vector<int> ret(n,-1), vis(n,0);
	
	int pos = n-1, dag = 1;
	function<void(int)> dfs = [&](int v) {
		vis[v] = 1;
		for (auto u : g[v]) {
			if (vis[u] == 1) dag = 0;
			else if (!vis[u]) dfs(u);
		}
		ret[pos--] = v, vis[v] = 2;
	};

	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

	if (!dag) ret.clear();	
	return ret;
}
```
