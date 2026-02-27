---
weight: 10
title: "pragma.cpp"
draft: false
toc: true
date: "2026-02-27T16:29:55-0300"
publishdate: "2026-02-27T16:29:55-0300"
description: ""
---

## Sobre
 Auto explicativo

Link original: [pragma.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/pragma.cpp)

## Código
```cpp
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
// Para operacoes com bits
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
```
