---
weight: 10
title: "MO - DSU"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Dado uma lista de arestas de um grafo, responde

 para cada query(l, r), quantos componentes conexos

 o grafo tem se soh considerar as arestas l, l+1, ..., r

 Da pra adaptar pra usar MO com qualquer estrutura rollbackavel



 O(m sqrt(q) log(n))



Link original: [moDsu.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/moDsu.cpp)

## Código
```cpp
struct dsu {
	int n, ans;
	vector<int> p, sz;
	stack<int> S;

	dsu(int n_) : n(n_), ans(n), p(n), sz(n) {
		for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
	}
	int find(int k) {
		while (p[k] != k) k = p[k];
		return k;
	}
	void add(pair<int, int> x) {
		int a = x.first, b = x.second;
		a = find(a), b = find(b);
		if (a == b) return S.push(-1);
		ans--;
		if (sz[a] > sz[b]) swap(a, b);
		S.push(a);
		sz[b] += sz[a];
		p[a] = b;
	}
	int query() { return ans; }
	void rollback() {
		int u = S.top(); S.pop();
		if (u == -1) return;
		sz[p[u]] -= sz[u];
		p[u] = u;
		ans++;
	}
};

int n;
vector<pair<int, int>> ar;

// 9d242b
vector<int> MO(vector<pair<int, int>> &q) {
	int SQ = sqrt(q.size()) + 1;
	int m = q.size();
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int l, int r) {
			if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
			return q[l].second < q[r].second;
			});
	vector<int> ret(m);

	dsu small(n);
	for (int i = 0; i < m; i++) {
		auto [l, r] = q[ord[i]];
		if (l / SQ == r / SQ) {
			for (int k = l; k <= r; k++) small.add(ar[k]);
			ret[ord[i]] = small.query();
			for (int k = l; k <= r; k++) small.rollback();
		}
	}

	for (int i = 0; i < m; i++) {
		dsu D(n);
		int fim = q[ord[i]].first/SQ*SQ + SQ - 1;
		int last_r = fim;
		int j = i-1;
		while (j+1 < m and q[ord[j+1]].first / SQ == q[ord[i]].first / SQ) {
			auto [l, r] = q[ord[++j]];

			if (l / SQ == r / SQ) continue;

			while (last_r < r) D.add(ar[++last_r]);
			for (int k = l; k <= fim; k++) D.add(ar[k]);

			ret[ord[j]] = D.query();

			for (int k = l; k <= fim; k++) D.rollback();
		}
		i = j;
	}
	return ret;
}
```
