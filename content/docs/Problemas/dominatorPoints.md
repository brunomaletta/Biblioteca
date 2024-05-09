---
weight: 10
title: "Dominator Points"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Se um ponto A tem ambas as coordenadas >= B, dizemos

 que A domina B

 is_dominated(p) fala se existe algum ponto no conjunto

 que domina p

 insert(p) insere p no conjunto

 (se p for dominado por alguem, nao vai inserir)

 o multiset 'quina' guarda informacao sobre os pontos

 nao dominados por um elemento do conjunto que nao dominam

 outro ponto nao dominado por um elemento do conjunto

 No caso, armazena os valores de x+y esses pontos



 Complexidades:

 is_dominated - O(log(n))

 insert - O(log(n)) amortizado

 query - O(1)



Link original: [dominatorPoints.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/dominatorPoints.cpp)

## Código
```cpp
struct dominator_points {
	set<pair<int, int>> se;
	multiset<int> quina;

	bool is_dominated(pair<int, int> p) {
		auto it = se.lower_bound(p);
		if (it == se.end()) return 0;
		return it->second >= p.second;
	}
	void mid(pair<int, int> a, pair<int, int> b, bool rem) {
		pair<int, int> m = {a.first+1, b.second+1};
		int val = m.first + m.second;
		if (!rem) quina.insert(val);
		else quina.erase(quina.find(val));
	}
	bool insert(pair<int, int> p) {
		if (is_dominated(p)) return 0;
		auto it = se.lower_bound(p);
		if (it != se.begin() and it != se.end())
			mid(*prev(it), *it, 1);
		while (it != se.begin()) {
			it--;
			if (it->second > p.second) break;
			if (it != se.begin()) mid(*prev(it), *it, 1);
			it = se.erase(it);
		}
		it = se.insert(p).first;
		if (it != se.begin()) mid(*prev(it), *it, 0);
		if (next(it) != se.end()) mid(*it, *next(it), 0);
		return 1;
	}
	int query() {
		if (!quina.size()) return INF;
		return *quina.begin();
	}
};
```
