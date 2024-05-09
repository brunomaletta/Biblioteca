---
weight: 10
title: "Produto de dois long long mod m"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 O(1)



Link original: [mulmod.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/mulmod.cpp)

## Código
```cpp
ll mul(ll a, ll b, ll m) { // a*b % m
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}
```
