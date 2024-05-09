---
weight: 10
title: "Hungaro"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Resolve o problema de assignment (matriz n x n)

 Colocar os valores da matriz em 'a' (pode < 0)

 assignment() retorna um par com o valor do

 assignment minimo, e a coluna escolhida por cada linha



 O(n^3)



Link original: [hungarian.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/hungarian.cpp)

## Código
```cpp
template<typename T> struct hungarian {
	int n;
	vector<vector<T>> a;
	vector<T> u, v;
	vector<int> p, way;
	T inf;

	hungarian(int n_) : n(n_), u(n+1), v(n+1), p(n+1), way(n+1) {
		a = vector<vector<T>>(n, vector<T>(n));
		inf = numeric_limits<T>::max();
	}
	pair<T, vector<int>> assignment() {
		for (int i = 1; i <= n; i++) {
			p[0] = i;
			int j0 = 0;
			vector<T> minv(n+1, inf);
			vector<int> used(n+1, 0);
			do {
				used[j0] = true;
				int i0 = p[j0], j1 = -1;
				T delta = inf;
				for (int j = 1; j <= n; j++) if (!used[j]) {
					T cur = a[i0-1][j-1] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, way[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
				for (int j = 0; j <= n; j++)
					if (used[j]) u[p[j]] += delta, v[j] -= delta;
					else minv[j] -= delta;
				j0 = j1;
			} while (p[j0] != 0);
			do {
				int j1 = way[j0];
				p[j0] = p[j1];
				j0 = j1;
			} while (j0);
		}
		vector<int> ans(n);
		for (int j = 1; j <= n; j++) ans[p[j]-1] = j-1;
		return make_pair(-v[0], ans);
	}
};
```
