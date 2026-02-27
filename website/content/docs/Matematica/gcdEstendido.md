---
weight: 10
title: "Euclides estendido"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Acha x e y tal que ax + by = mdc(a, b) (nao eh unico)

 Assume a, b >= 0



 O(log(min(a, b)))



Link original: [gcdEstendido.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/gcdEstendido.cpp)

## Código
```cpp
tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b%a, a);
    return {g, y - b/a*x, x};
}
```
