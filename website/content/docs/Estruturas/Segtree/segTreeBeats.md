---
weight: 10
title: "SegTree Beats"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 query(a, b) - {{min(v[a..b]), max(v[a..b])}, sum(v[a..b])}

 updatemin(a, b, x) faz com que v[i] <- min(v[i], x),

 para i em [a, b]

 updatemax faz o mesmo com max, e updatesum soma x

 em todo mundo do intervalo [a, b]



 Complexidades:

 build - O(n)

 query - O(log(n))

 update - O(log^2 (n)) amortizado

 (se nao usar updatesum, fica log(n) amortizado)



Link original: [segTreeBeats.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTreeBeats.cpp)

## Código
```cpp
#define f first
#define s second

namespace beats {
	struct node {
		int tam;
		ll sum, lazy; // lazy pra soma
		ll mi1, mi2, mi; // mi = #mi1
		ll ma1, ma2, ma; // ma = #ma1

		node(ll x = 0) {
			sum = mi1 = ma1 = x;
			mi2 = LINF, ma2 = -LINF;
			mi = ma = tam = 1;
			lazy = 0;
		}
		node(const node& l, const node& r) {
			sum = l.sum + r.sum, tam = l.tam + r.tam;
			lazy = 0;
			if (l.mi1 > r.mi1) {
				mi1 = r.mi1, mi = r.mi;
				mi2 = min(l.mi1, r.mi2);
			} else if (l.mi1 < r.mi1) {
				mi1 = l.mi1, mi = l.mi;
				mi2 = min(r.mi1, l.mi2);
			} else {
				mi1 = l.mi1, mi = l.mi+r.mi;
				mi2 = min(l.mi2, r.mi2);
			}
			if (l.ma1 < r.ma1) {
				ma1 = r.ma1, ma = r.ma;
				ma2 = max(l.ma1, r.ma2);
			} else if (l.ma1 > r.ma1) {
				ma1 = l.ma1, ma = l.ma;
				ma2 = max(r.ma1, l.ma2);
			} else {
				ma1 = l.ma1, ma = l.ma+r.ma;
				ma2 = max(l.ma2, r.ma2);
			}
		}
		void setmin(ll x) {
			if (x >= ma1) return;
			sum += (x - ma1)*ma;
			if (mi1 == ma1) mi1 = x;
			if (mi2 == ma1) mi2 = x;
			ma1 = x;
		}
		void setmax(ll x) {
			if (x <= mi1) return;
			sum += (x - mi1)*mi;
			if (ma1 == mi1) ma1 = x;
			if (ma2 == mi1) ma2 = x;
			mi1 = x;
		}
		void setsum(ll x) {
			mi1 += x, mi2 += x, ma1 += x, ma2 += x;
			sum += x*tam;
			lazy += x;
		}
	};

	node seg[4*MAX];
	int n, *v;

	node build(int p=1, int l=0, int r=n-1) {
		if (l == r) return seg[p] = {v[l]};
		int m = (l+r)/2;
		return seg[p] = {build(2*p, l, m), build(2*p+1, m+1, r)};
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		if (l == r) return;
		for (int k = 0; k < 2; k++) {
			if (seg[p].lazy) seg[2*p+k].setsum(seg[p].lazy);
			seg[2*p+k].setmin(seg[p].ma1);
			seg[2*p+k].setmax(seg[p].mi1);
		}
		seg[p].lazy = 0;
	}
	pair<pair<ll, ll>, ll> query(int a, int b, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return {{LINF, -LINF}, 0};
		if (a <= l and r <= b) return {{seg[p].mi1, seg[p].ma1}, seg[p].sum};
		prop(p, l, r);
		int m = (l+r)/2;
		auto L = query(a, b, 2*p, l, m), R = query(a, b, 2*p+1, m+1, r);
		return {{min(L.f.f, R.f.f), max(L.f.s, R.f.s)}, L.s+R.s};
	}
	node updatemin(int a, int b, ll x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a or seg[p].ma1 <= x) return seg[p];
		if (a <= l and r <= b and seg[p].ma2 < x) {
			seg[p].setmin(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatemin(a, b, x, 2*p, l, m),
						updatemin(a, b, x, 2*p+1, m+1, r)};
	}
	node updatemax(int a, int b, ll x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a or seg[p].mi1 >= x) return seg[p];
		if (a <= l and r <= b and seg[p].mi2 > x) {
			seg[p].setmax(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatemax(a, b, x, 2*p, l, m),
						updatemax(a, b, x, 2*p+1, m+1, r)};
	}
	node updatesum(int a, int b, ll x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			seg[p].setsum(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatesum(a, b, x, 2*p, l, m),
						updatesum(a, b, x, 2*p+1, m+1, r)};
	}
};
```
