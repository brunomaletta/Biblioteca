---
weight: 10
title: "SegTree"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Recursiva com Lazy Propagation

 Query: soma do range [a, b]

 Update: soma x em cada elemento do range [a, b]

 Pode usar a seguinte funcao para indexar os nohs:

 f(l, r) = (l+r)|(l!=r), usando 2N de memoria



 Complexidades:

 build - O(n)

 query - O(log(n))

 update - O(log(n))



Link original: [segTree.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTree.cpp)

## Código
```cpp
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n, *v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p] += lazy[p]*(r-l+1);
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return 0;
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}
	ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = update(a, b, x, 2*p, l, m) +
			update(a, b, x, 2*p+1, m+1, r);
	}
};


// Se tiver uma seg de max, da pra descobrir em O(log(n))
// o primeiro e ultimo elemento >= val numa range:

// primeira posicao >= val em [a, b] (ou -1 se nao tem)
int get_left(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	prop(p, l, r);
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_left(a, b, val, 2*p, l, m);
	if (x != -1) return x;
	return get_left(a, b, val, 2*p+1, m+1, r);
}

// ultima posicao >= val em [a, b] (ou -1 se nao tem)
int get_right(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	prop(p, l, r);
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_right(a, b, val, 2*p+1, m+1, r);
	if (x != -1) return x;
	return get_right(a, b, val, 2*p, l, m);
}

// Se tiver uma seg de soma sobre um array nao negativo v, da pra
// descobrir em O(log(n)) o maior j tal que v[i]+v[i+1]+...+v[j-1] < val
int lower_bound(int i, ll& val, int p, int l, int r) {
	prop(p, l, r);
	if (r < i) return n;
	if (i <= l and seg[p] < val) {
		val -= seg[p];
		return n;
	}
	if (l == r) return l;
	int m = (l+r)/2;
	int x = lower_bound(i, val, 2*p, l, m);
	if (x != n) return x;
	return lower_bound(i, val, 2*p+1, m+1, r);
}
```
