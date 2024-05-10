---
weight: 10
title: "AGM Direcionada"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Fala o menor custo para selecionar arestas tal que

 o vertice 'r' alcance todos

 Se nao tem como, retorna LINF



 O(m log(n))



Link original: [directedMst.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/directedMst.cpp)

## Código
```cpp
struct node {
	pair<ll, int> val;
	ll lazy;
	node *l, *r;
	node() {}
	node(pair<int, int> v) : val(v), lazy(0), l(NULL), r(NULL) {}

	void prop() {
		val.first += lazy;
		if (l) l->lazy += lazy;
		if (r) r->lazy += lazy;
		lazy = 0;
	}
};
void merge(node*& a, node* b) {
	if (!a) swap(a, b);
	if (!b) return;
	a->prop(), b->prop();
	if (a->val > b->val) swap(a, b);
	merge(rand()%2 ? a->l : a->r, b);
}
pair<ll, int> pop(node*& R) {
	R->prop();
	auto ret = R->val;
	node* tmp = R;
	merge(R->l, R->r);
	R = R->l;
	if (R) R->lazy -= ret.first;
	delete tmp;
	return ret;
}
void apaga(node* R) { if (R) apaga(R->l), apaga(R->r), delete R; }

ll dmst(int n, int r, vector<pair<pair<int, int>, int>>& ar) {
	vector<int> p(n); iota(p.begin(), p.end(), 0);
	function<int(int)> find = [&](int k) { return p[k]==k?k:p[k]=find(p[k]); };
	vector<node*> h(n);
	for (auto e : ar) merge(h[e.first.second], new node({e.second, e.first.first}));
	vector<int> pai(n, -1), path(n);
	pai[r] = r;
	ll ans = 0;

	for (int i = 0; i < n; i++) { // vai conectando todo mundo
		int u = i, at = 0;
		while (pai[u] == -1) {
			if (!h[u]) { // nao tem
				for (auto i : h) apaga(i);
				return LINF;
			}
			path[at++] = u, pai[u] = i;
			auto [mi, v] = pop(h[u]);
			ans += mi;

			if (pai[u = find(v)] == i) { // ciclo
				while (find(v = path[--at]) != u)
					merge(h[u], h[v]), h[v] = NULL, p[find(v)] = u;
				pai[u] = -1;
			}
		}
	}
	for (auto i : h) apaga(i);
	return ans;
}
```
