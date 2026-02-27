---
weight: 10
title: "Gray Code"
draft: false
toc: true
date: "2026-02-27T17:02:42-0300"
publishdate: "2026-02-27T17:02:42-0300"
description: ""
---

## Sobre
 Gera uma permutacao de 0 a 2^n-1, de forma que

 duas posicoes adjacentes diferem em exatamente 1 bit



 O(2^n)



Link original: [grayCode.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/grayCode.cpp)

## Código
```cpp
vector<int> gray_code(int n) {
	vector<int> ret(1<<n);
	for (int i = 0; i < (1<<n); i++) ret[i] = i^(i>>1);
	return ret;
}
```
