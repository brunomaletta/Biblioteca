---
weight: 10
title: "Order Statistic Set"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Funciona do C++11 pra cima



Link original: [orderStatisticSet.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/orderStatisticSet.cpp)

## Código
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
// para declarar:
// ord_set<int> s;
// coisas do set normal funcionam:
// for (auto i : s) cout << i << endl;
// cout << s.size() << endl;
// k-esimo maior elemento O(log|s|):
// k=0: menor elemento
// cout << *s.find_by_order(k) << endl;
// quantos sao menores do que k O(log|s|):
// cout << s.order_of_key(k) << endl;

// Para fazer um multiset, tem que
// usar ord_set<pair<int, int>> com o
// segundo parametro sendo algo para diferenciar
// os ementos iguais.
// s.order_of_key({k, -INF}) vai retornar o
// numero de elementos < k
```
