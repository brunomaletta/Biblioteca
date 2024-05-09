---
weight: 10
title: "RMQ com Divide and Conquer"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Responde todas as queries em

 O(n log(n))



Link original: [rmqOffline.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/rmqOffline.cpp)

## Código
```cpp
typedef pair<pair<int, int>, int> iii;
#define f first
#define s second

int n, q, v[MAX];
iii qu[MAX];
int ans[MAX], pref[MAX], sulf[MAX];

void solve(int l=0, int r=n-1, int ql=0, int qr=q-1) {
	if (l > r or ql > qr) return;
	int m = (l+r)/2;
	int qL = partition(qu+ql, qu+qr+1, [=](iii x){return x.f.s < m;}) - qu;
	int qR = partition(qu+qL, qu+qr+1, [=](iii x){return x.f.f <=m;}) - qu;

	pref[m] = sulf[m] = v[m];
	for (int i = m-1; i >= l; i--) pref[i] = min(v[i], pref[i+1]);
	for (int i = m+1; i <= r; i++) sulf[i] = min(v[i], sulf[i-1]);

	for (int i = qL; i < qR; i++)
		ans[qu[i].s] = min(pref[qu[i].f.f], sulf[qu[i].f.s]);

	solve(l, m-1, ql, qL-1), solve(m+1, r, qR, qr);
}
```
