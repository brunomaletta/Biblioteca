---
weight: 10
title: "Totiente"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 O(sqrt(n))



Link original: [totiente.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/totiente.cpp)

## Código
```cpp
int tot(int n){
	int ret = n;

	for (int i = 2; i*i <= n; i++) if (n % i == 0) {
		while (n % i == 0) n /= i;
		ret -= ret / i;
	}
	if (n > 1) ret -= ret / n;

	return ret;
}
```
