---
weight: 10
title: "Conectividade Dinamica DC"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Offline com Divide and Conquer e

 DSU com rollback

 O(n log^2(n))



Link original: [conectividadeDinamica.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/conectividadeDinamica.cpp)

## Código
```cpp
typedef pair<int, int> T;

namespace data {
	int n, ans;
	int p[MAX], sz[MAX];
	stack<int> S;

	void build(int n2) {
		n = n2;
		for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
		ans = n;
	}
	int find(int k) {
		while (p[k] != k) k = p[k];
		return k;
	}
	void add(T x) {
		int a = x.first, b = x.second;
		a = find(a), b = find(b);
		if (a == b) return S.push(-1);
		ans--;
		if (sz[a] > sz[b]) swap(a, b);
		S.push(a);
		sz[b] += sz[a];
		p[a] = b;
	}
	int query() {
		return ans;
	}
	void rollback() {
		int u = S.top(); S.pop();
		if (u == -1) return;
		sz[p[u]] -= sz[u];
		p[u] = u;
		ans++;
	}
};

int ponta[MAX]; // outra ponta do intervalo ou -1 se for query
int ans[MAX], n, q;
T qu[MAX];

void solve(int l = 0, int r = q-1) {
	if (l >= r) {
		ans[l] = data::query(); // agora a estrutura ta certa
		return;
	}
	int m = (l+r)/2, qnt = 1;
	for (int i = m+1; i <= r; i++) if (ponta[i]+1 and ponta[i] < l)
		data::add(qu[i]), qnt++;
	solve(l, m);
	while (--qnt) data::rollback();
	for (int i = l; i <= m; i++) if (ponta[i]+1 and ponta[i] > r)
		data::add(qu[i]), qnt++;
	solve(m+1, r);
	while (qnt--) data::rollback();
}
```
