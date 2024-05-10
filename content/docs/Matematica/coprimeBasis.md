---
weight: 10
title: "Coprime Basis"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Dado um conjunto de elementos A constroi uma base B

 de fatores coprimos tal que todo elemento A[i]

 pode ser fatorado como A[i] = \prod B[j]^p_ij



 Sendo n o numero de inserts, a complexidade esperada fica

 O(n*(n*loglog(MAX) + log(MAX)^2))



 No pior caso, podemos trocar n*loglog(MAX) por

  8n, se MAX <= 1e6

 10n, se MAX <= 1e9

 16n, se MAX <= 1e18

 26n, se MAX <= 1e36



Link original: [coprimeBasis.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/coprimeBasis.cpp)

## Código
```cpp
template <typename T> struct coprime_basis {
	vector<T> basis;

	coprime_basis() {}
	coprime_basis(vector<T> v) { for (T i : v) insert(i); }

	void insert(T z) {
		int n = basis.size();
		basis.push_back(z);
		for (int i = n; i < basis.size(); i++) {
			for (int j = (i != n) ? i+1 : 0; j < basis.size(); j++) {
				if (i == j) continue;
				T &x = basis[i];
				if (x == 1) {
					j = INF;
					continue;
				}
				T &y = basis[j];
				T g = gcd(x, y);
				if (g == 1) continue;
				y /= g, x /= g;
				basis.push_back(g);
			}
		}
		basis.erase(remove(basis.begin(), basis.end(), 1), basis.end());
	}

	vector<int> factor(T x) {
		vector<int> fat(basis.size());
		for (int i = 0; i < basis.size(); i++) {
			while (x % basis[i] == 0) x /= basis[i], fat[i]++;
		}
		return fat;
	}
};
```
