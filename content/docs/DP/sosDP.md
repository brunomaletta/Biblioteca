---
weight: 10
title: "SOS DP"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 O(n 2^n)



 soma de sub-conjunto

Link original: [sosDP.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/DP/sosDP.cpp)

## Código
```cpp
vector<ll> sos_dp(vector<ll> f) {
	int N = __builtin_ctz(f.size());
	assert((1<<N) == f.size());

	for (int i = 0; i < N; i++) for (int mask = 0; mask < (1<<N); mask++)
		if (mask>>i&1) f[mask] += f[mask^(1<<i)];
	return f;
}

// soma de super-conjunto
vector<ll> sos_dp(vector<ll> f) {
	int N = __builtin_ctz(f.size());
	assert((1<<N) == f.size());

	for (int i = 0; i < N; i++) for (int mask = 0; mask < (1<<N); mask++)
		if (~mask>>i&1) f[mask] += f[mask^(1<<i)];
	return f;
}
```
