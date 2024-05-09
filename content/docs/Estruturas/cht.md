---
weight: 10
title: "Convex Hull Trick Estatico"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 adds tem que serem feitos em ordem de slope

 queries tem que ser feitas em ordem de x



 add O(1) amortizado, get O(1) amortizado



Link original: [cht.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/cht.cpp)

## Código
```cpp
struct CHT {
	int it;
	vector<ll> a, b;
	CHT():it(0){}
	ll eval(int i, ll x){
		return a[i]*x + b[i];
	}
	bool useless(){
		int sz = a.size();
		int r = sz-1, m = sz-2, l = sz-3;
#warning cuidado com overflow!
		return (b[l] - b[r])*(a[m] - a[l]) <
			(b[l] - b[m])*(a[r] - a[l]);
	}
	void add(ll A, ll B){
		a.push_back(A); b.push_back(B);
		while (!a.empty()){
			if ((a.size() < 3) || !useless()) break;
			a.erase(a.end() - 2);
			b.erase(b.end() - 2);
		}
		it = min(it, int(a.size()) - 1);
	}
	ll get(ll x){
		while (it+1 < a.size()){
			if (eval(it+1, x) > eval(it, x)) it++;
			else break;
		}
		return eval(it, x);
	}
};
```
