---
weight: 10
title: "Sparse Table"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Resolve RMQ

 MAX2 = log(MAX)



 Complexidades:

 build - O(n log(n))

 query - O(1)



Link original: [sparseTable.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/sparseTable.cpp)

## Código
```cpp
namespace sparse {
	int m[MAX2][MAX], n;
	void build(int n2, int* v) {
		n = n2;
		for (int i = 0; i < n; i++) m[0][i] = v[i];
		for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
			m[j][i] = min(m[j-1][i], m[j-1][i+(1<<(j-1))]);
	}
	int query(int a, int b) {
		int j = __builtin_clz(1) - __builtin_clz(b-a+1);
		return min(m[j][a], m[j][b-(1<<j)+1]);
	}
}
```
