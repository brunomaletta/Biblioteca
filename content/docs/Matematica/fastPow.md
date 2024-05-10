---
weight: 10
title: "Exponenciacao rapida"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 (x^y mod m) em O(log(y))



Link original: [fastPow.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/fastPow.cpp)

## Código
```cpp
ll pow(ll x, ll y, ll m) { // iterativo
	ll ret = 1;
	while (y) {
		if (y & 1) ret = (ret * x) % m;
		y >>= 1;
		x = (x * x) % m;
	}
	return ret;
}

ll pow(ll x, ll y, ll m) { // recursivo
	if (!y) return 1;
	ll ans = pow(x*x%m, y/2, m);
	return y%2 ? x*ans%m : ans;
}
```
