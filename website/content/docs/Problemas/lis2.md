---
weight: 10
title: "LIS - tamanho"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Calcula o tamanho da LIS



 O(n log(n))



Link original: [lis2.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/lis2.cpp)

## Código
```cpp
template<typename T> int lis(vector<T> &v){
	vector<T> ans;
	for (T t : v){
		// Para non-decreasing use upper_bound()
		auto it = lower_bound(ans.begin(), ans.end(), t);
		if (it == ans.end()) ans.push_back(t);
		else *it = t;
	}
	return ans.size();
}
```
