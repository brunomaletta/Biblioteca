---
weight: 10
title: "rand.cpp"
draft: false
toc: true
date: "2026-02-27T17:02:42-0300"
publishdate: "2026-02-27T17:02:42-0300"
description: ""
---

## Sobre
Link original: [rand.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/rand.cpp)

## Código
```cpp
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
```
