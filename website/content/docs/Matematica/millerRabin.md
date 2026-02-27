---
weight: 10
title: "Miller-Rabin"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Testa se n eh primo, n <= 3 * 10^18



 O(log(n)), considerando multiplicacao

 e exponenciacao constantes



Link original: [millerRabin.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/millerRabin.cpp)

## Código
```cpp
ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;
	ll ans = pow(mul(x, x, m), y/2, m);
	return y%2 ? mul(x, ans, m) : ans;
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;
	ll r = __builtin_ctzll(n - 1), d = n >> r;

 	// com esses primos, o teste funciona garantido para n <= 2^64
	// funciona para n <= 3*10^24 com os primos ate 41
	for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ll x = pow(a, d, n);
		if (x == 1 or x == n - 1 or a % n == 0) continue;
		
		for (int j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) break;
		}
		if (x != n - 1) return 0;
	}
	return 1;
}
```
