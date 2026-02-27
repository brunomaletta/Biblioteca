---
weight: 10
title: "19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());"
draft: false
toc: true
date: "2026-02-27T16:24:59-0300"
publishdate: "2026-02-27T16:24:59-0300"
description: ""
---

## Sobre
Link original: [rand.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/rand.cpp)

## Código
```cpp
int uniform(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
```
