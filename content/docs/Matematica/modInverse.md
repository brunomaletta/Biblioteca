---
weight: 10
title: "Inverso Modular"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Computa o inverso de a modulo b

 Se b eh primo, basta fazer

 a^(b-2)



Link original: [modInverse.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/modInverse.cpp)

## Código
```cpp
ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}

// computa o inverso modular de 1..MAX-1 modulo um primo
ll inv[MAX]:
inv[1] = 1;
for (int i = 2; i < MAX; i++) inv[i] = MOD - MOD/i*inv[MOD%i]%MOD;
```
