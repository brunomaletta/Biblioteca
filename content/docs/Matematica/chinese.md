---
weight: 10
title: "Teorema Chines do Resto"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Combina equacoes modulares lineares: x = a (mod m)

 O m final eh o lcm dos m's, e a resposta eh unica mod o lcm

 Os m nao precisam ser coprimos

 Se nao tiver solucao, o 'a' vai ser -1



Link original: [chinese.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/chinese.cpp)

## Código
```cpp
template<typename T> tuple<T, T, T> ext_gcd(T a, T b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b%a, a);
    return {g, y - b/a*x, x};
}

template<typename T = ll> struct crt {
	T a, m;

	crt() : a(0), m(1) {}
	crt(T a_, T m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		auto [g, x, y] = ext_gcd(m, C.m);
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		T lcm = m/g*C.m;
		T ans = a + (x*(C.a-a)/g % (C.m/g))*m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
};
```
