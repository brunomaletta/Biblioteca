---
weight: 10
title: "Logaritmo Discreto"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Resolve logaritmo discreto com o algoritmo baby step giant step

 Encontra o menor x tal que a^x = b (mod m)

 Se nao tem, retorna -1



 O(sqrt(m) * log(sqrt(m))

Link original: [logDiscreto.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/logDiscreto.cpp)

## Código
```cpp

int dlog(int b, int a, int m) {
	if (a == 0) return b ? -1 : 1; // caso nao definido

	a %= m, b %= m;
	int k = 1, shift = 0;
	while (1) {
		int g = gcd(a, m);
		if (g == 1) break;

		if (b == k) return shift;
		if (b % g) return -1;
		b /= g, m /= g, shift++;
		k = (ll) k * a / g % m;
	}

	int sq = sqrt(m)+1, giant = 1;
	for (int i = 0; i < sq; i++) giant = (ll) giant * a % m;

	vector<pair<int, int>> baby;
	for (int i = 0, cur = b; i <= sq; i++) {
		baby.emplace_back(cur, i);
		cur = (ll) cur * a % m;
	}
	sort(baby.begin(), baby.end());

	for (int j = 1, cur = k; j <= sq; j++) {
		cur = (ll) cur * giant % m;
		auto it = lower_bound(baby.begin(), baby.end(), pair(cur, INF));
		if (it != baby.begin() and (--it)->first == cur)
			return sq * j - it->second + shift;
	}

	return -1;
}
```
