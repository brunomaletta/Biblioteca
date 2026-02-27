---
weight: 10
title: "Distinct Range Query"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 build - O(n (log n + log(sigma)))

 query - O(log(sigma))



Link original: [distinct.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/distinct.cpp)

## Código
```cpp
namespace perseg { };

int qt[MAX];

void build(vector<int>& v) {
	int n = v.size();
	perseg::build(n);
	map<int, int> last;
	int at = 0;
	for (int i = 0; i < n; i++) {
		if (last.count(v[i])) {
			perseg::update(last[v[i]], -1);
			at++;
		}
		perseg::update(i, 1);
		qt[i] = ++at;
		last[v[i]] = i;
	}
}

int query(int l, int r) {
	return perseg::query(l, r, qt[r]);
}
```
