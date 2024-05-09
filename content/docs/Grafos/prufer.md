---
weight: 10
title: "Prufer code"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Traduz de lista de arestas para prufer code

 e vice-versa

 Os vertices tem label de 0 a n-1

 Todo array com n-2 posicoes e valores de

 0 a n-1 sao prufer codes validos

 

 O(n)



Link original: [prufer.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/prufer.cpp)

## Código
```cpp
vector<int> to_prufer(vector<pair<int, int>> tree) {
	int n = tree.size()+1;
	vector<int> d(n, 0);
	vector<vector<int>> g(n);
	for (auto [a, b] : tree) d[a]++, d[b]++,
		g[a].push_back(b), g[b].push_back(a);
	vector<int> pai(n, -1);
	queue<int> q; q.push(n-1);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) if (v != pai[u])
			pai[v] = u, q.push(v);
	}
	int idx, x;
	idx = x = find(d.begin(), d.end(), 1) - d.begin();
	vector<int> ret;
	for (int i = 0; i < n-2; i++) {
		int y = pai[x];
		ret.push_back(y);
		if (--d[y] == 1 and y < idx) x = y;
		else idx = x = find(d.begin()+idx+1, d.end(), 1) - d.begin();
	}
	return ret;
}

vector<pair<int, int>> from_prufer(vector<int> p) {
	int n = p.size()+2;
	vector<int> d(n, 1);
	for (int i : p) d[i]++;
	p.push_back(n-1);
	int idx, x;
	idx = x = find(d.begin(), d.end(), 1) - d.begin();
	vector<pair<int, int>> ret;
	for (int y : p) {
		ret.push_back({x, y});
		if (--d[y] == 1 and y < idx) x = y;
		else idx = x = find(d.begin()+idx+1, d.end(), 1) - d.begin();
	}
	return ret;
}

```
