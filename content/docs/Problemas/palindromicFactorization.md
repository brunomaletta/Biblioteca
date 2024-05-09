---
weight: 10
title: "Palindromic Factorization"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Precisa da eertree

 Computa o numero de formas de particionar cada

 prefixo da string em strings palindromicas



 O(n log n), considerando alfabeto O(1)



Link original: [palindromicFactorization.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/palindromicFactorization.cpp)

## Código
```cpp
struct eertree { ... };

ll factorization(string s) {
	int n = s.size(), sz = 2;
	eertree PT(n);
	vector<int> diff(n+2), slink(n+2), sans(n+2), dp(n+1);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		PT.add(s[i-1]);
		if (PT.size()+2 > sz) {
			diff[sz] = PT.len[sz] - PT.len[PT.link[sz]];
			if (diff[sz] == diff[PT.link[sz]])
				slink[sz] = slink[PT.link[sz]];
			else slink[sz] = PT.link[sz];
			sz++;
		}
		for (int v = PT.last; PT.len[v] > 0; v = slink[v]) {
			sans[v] = dp[i - (PT.len[slink[v]] + diff[v])];
			if (diff[v] == diff[PT.link[v]])
				sans[v] = (sans[v] + sans[PT.link[v]]) % MOD;
			dp[i] = (dp[i] + sans[v]) % MOD;
		}
	}
	return dp[n];
}

```
