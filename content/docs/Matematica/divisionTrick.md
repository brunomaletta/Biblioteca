---
weight: 10
title: "Division Trick"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Gera o conjunto n/i, pra todo i, em O(sqrt(n))

 copiei do github do tfg50



Link original: [divisionTrick.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/divisionTrick.cpp)

## Código
```cpp
for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// n / i has the same value for l <= i <= r
}
```
