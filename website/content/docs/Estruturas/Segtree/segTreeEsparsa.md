---
weight: 10
title: "SegTree Esparsa - Lazy"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Query: soma do range [a, b]

 Update: flipa os valores de [a, b]

 O MAX tem q ser Q log N para Q updates



 Complexidades:

 build - O(1)

 query - O(log(n))

 update - O(log(n))



Link original: [segTreeEsparsa.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTreeEsparsa.cpp)

## Código
```cpp
namespace seg {
	int seg[MAX], lazy[MAX], R[MAX], L[MAX], ptr;
	int get_l(int i){
		if (L[i] == 0) L[i] = ptr++;
		return L[i];
	}
	int get_r(int i){
		if (R[i] == 0) R[i] = ptr++;
		return R[i];
	}

	void build() { ptr = 2; }

	void prop(int p, int l, int r) {
		if (!lazy[p]) return;
		seg[p] = r-l+1 - seg[p];
		if (l != r) lazy[get_l(p)]^=lazy[p], lazy[get_r(p)]^=lazy[p];
		lazy[p] = 0;
	}

	int query(int a, int b, int p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];

		int m = (l+r)/2;
		return query(a, b, get_l(p), l, m)+query(a, b, get_r(p), m+1, r);
	}

	int update(int a, int b, int p=1, int l=0, int r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			lazy[p] ^= 1;
			prop(p, l, r);
			return seg[p];
		}
		int m = (l+r)/2;
		return seg[p] = update(a, b, get_l(p), l, m)+update(a, b, get_r(p), m+1, r);
	}
};
```
