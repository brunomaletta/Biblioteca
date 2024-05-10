---
weight: 10
title: "Binomial Distribution"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 binom(n, k, p) retorna a probabilidade de k sucessos

 numa binomial(n, p)



Link original: [probabilityBinomial.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/probabilityBinomial.cpp)

## Código
```cpp
double logfact[MAX];

void calc() {
	logfact[0] = 0;
	for (int i = 1; i < MAX; i++) logfact[i] = logfact[i-1] + log(i);
}

double binom(int n, int k, double p) {
	return exp(logfact[n] - logfact[k] - logfact[n-k] + k * log(p) + (n-k) * log(1 - p));
}
```
