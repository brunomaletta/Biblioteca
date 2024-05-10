---
weight: 10
title: "SegTree Persistente"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 SegTree de soma, update de somar numa posicao



 query(a, b, t) retorna a query de [a, b] na versao t

 update(a, x, t) faz um update v[a]+=x a partir da

 versao de t, criando uma nova versao e retornando seu id

 Por default, faz o update a partir da ultima versao



 build - O(n)

 query - O(log(n))

 update - O(log(n))



Link original: [segTreePersistent.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTreePersistent.cpp)

## Código
```cpp
const int MAX = 1e5+10, UPD = 1e5+10, LOG = 18;
const int MAXS = 2*MAX+UPD*LOG;

namespace perseg {
	ll seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n, *v;

	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	ll query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return query(a, b, L[p], l, m) + query(a, b, R[p], m+1, r);
	}
	ll query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	ll update(int a, int x, int lp, int p, int l, int r) {
		if (l == r) return seg[p] = seg[lp]+x;
		int m = (l+r)/2;
		if (a <= m)
			return seg[p] = update(a, x, L[lp], L[p]=cnt++, l, m) + seg[R[p]=R[lp]];
		return seg[p] = seg[L[p]=L[lp]] + update(a, x, R[lp], R[p]=cnt++, m+1, r);
	}
	int update(int a, int x, int tt=t) {
		update(a, x, rt[tt], rt[++t]=cnt++, 0, n-1);
		return t;
	}
};
```
