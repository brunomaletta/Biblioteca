---
weight: 10
title: "Line Tree"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Reduz min-query em arvore para RMQ

 Se o grafo nao for uma arvore, as queries

 sao sobre a arvore geradora maxima

 Queries de minimo



 build - O(n log(n))

 query - O(log(n))



Link original: [linetree.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/linetree.cpp)

## Código
```cpp
int n;

namespace linetree {
	int id[MAX], seg[2*MAX], pos[MAX];
	vector<int> v[MAX], val[MAX];
	vector<pair<int, pair<int, int> > > ar;

	void add(int a, int b, int p) { ar.push_back({p, {a, b}}); }
	void build() {
		sort(ar.rbegin(), ar.rend());
		for (int i = 0; i < n; i++) id[i] = i, v[i] = {i}, val[i].clear();
		for (auto i : ar) {
			int a = id[i.second.first], b = id[i.second.second];
			if (a == b) continue;
			if (v[a].size() < v[b].size()) swap(a, b);
			for (auto j : v[b]) id[j] = a, v[a].push_back(j);
			val[a].push_back(i.first);
			for (auto j : val[b]) val[a].push_back(j);
			v[b].clear(), val[b].clear();
		}
		vector<int> vv;
		for (int i = 0; i < n; i++) for (int j = 0; j < v[i].size(); j++) {
			pos[v[i][j]] = vv.size();
			if (j + 1 < v[i].size()) vv.push_back(val[i][j]);
			else vv.push_back(0);
		}
		for (int i = n; i < 2*n; i++) seg[i] = vv[i-n];
		for (int i = n-1; i; i--) seg[i] = min(seg[2*i], seg[2*i+1]);
	}
	int query(int a, int b) {
		if (id[a] != id[b]) return 0; // nao estao conectados
		a = pos[a], b = pos[b];
		if (a > b) swap(a, b);
		b--;
		int ans = INF;
		for (a += n, b += n; a <= b; ++a/=2, --b/=2) ans = min({ans, seg[a], seg[b]});
		return ans;
	}
};
```
