---
weight: 10
title: "Wavelet Tree"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Usa O(sigma + n log(sigma)) de memoria,

 onde sigma = MAXN - MINN

 Depois do build, o v fica ordenado

 count(i, j, x, y) retorna o numero de elementos de

 v[i, j) que pertencem a [x, y]

 kth(i, j, k) retorna o elemento que estaria

 na poscicao k-1 de v[i, j), se ele fosse ordenado

 sum(i, j, x, y) retorna a soma dos elementos de

 v[i, j) que pertencem a [x, y]

 sumk(i, j, k) retorna a soma dos k-esimos menores

 elementos de v[i, j) (sum(i, j, 1) retorna o menor)



 Complexidades:

 build - O(n log(sigma))

 count - O(log(sigma))

 kth   - O(log(sigma))

 sum   - O(log(sigma))

 sumk  - O(log(sigma))



Link original: [waveletTree.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/waveletTree.cpp)

## Código
```cpp
int n, v[MAX];
vector<int> esq[4*(MAXN-MINN)], pref[4*(MAXN-MINN)];

void build(int b = 0, int e = n, int p = 1, int l = MINN, int r = MAXN) {
	int m = (l+r)/2; esq[p].push_back(0); pref[p].push_back(0);
	for (int i = b; i < e; i++) {
		esq[p].push_back(esq[p].back()+(v[i]<=m));
		pref[p].push_back(pref[p].back()+v[i]);
	}
	if (l == r) return;
	int m2 = stable_partition(v+b, v+e, [=](int i){return i <= m;}) - v;
	build(b, m2, 2*p, l, m), build(m2, e, 2*p+1, m+1, r);
}

int count(int i, int j, int x, int y, int p = 1, int l = MINN, int r = MAXN) {
	if (y < l or r < x) return 0;
	if (x <= l and r <= y) return j-i;
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	return count(ei, ej, x, y, 2*p, l, m)+count(i-ei, j-ej, x, y, 2*p+1, m+1, r);
}

int kth(int i, int j, int k, int p=1, int l = MINN, int r = MAXN) {
	if (l == r) return l;
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	if (k <= ej-ei) return kth(ei, ej, k, 2*p, l, m);
	return kth(i-ei, j-ej, k-(ej-ei), 2*p+1, m+1, r);
}

int sum(int i, int j, int x, int y, int p = 1, int l = MINN, int r = MAXN) {
	if (y < l or r < x) return 0;
	if (x <= l and r <= y) return pref[p][j]-pref[p][i];
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	return sum(ei, ej, x, y, 2*p, l, m) + sum(i-ei, j-ej, x, y, 2*p+1, m+1, r);
}

int sumk(int i, int j, int k, int p = 1, int l = MINN, int r = MAXN) {
	if (l == r) return l*k;
	int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
	if (k <= ej-ei) return sumk(ei, ej, k, 2*p, l, m);
	return pref[2*p][ej]-pref[2*p][ei]+sumk(i-ei, j-ej, k-(ej-ei), 2*p+1, m+1, r);
}
```
