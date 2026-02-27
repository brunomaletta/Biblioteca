---
weight: 10
title: "Inversion Count"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Computa o numero de inversoes para transformar

 l em r (se nao tem como, retorna -1)



 O(n log(n))



Link original: [inversionCount.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/inversionCount.cpp)

## Código
```cpp
template<typename T> ll inv_count(vector<T> l, vector<T> r = {}) {
	if (!r.size()) {
		r = l;
		sort(r.begin(), r.end());
	}
	int n = l.size();
	vector<int> v(n), bit(n);
	vector<pair<T, int>> w;
	for (int i = 0; i < n; i++) w.push_back({r[i], i+1});
	sort(w.begin(), w.end());
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(w.begin(), w.end(), make_pair(l[i], 0));
		if (it == w.end() or it->first != l[i]) return -1; // nao da
		v[i] = it->second;
		it->second = -1;
	}

	ll ans = 0;
	for (int i = n-1; i >= 0; i--) {
		for (int j = v[i]-1; j; j -= j&-j) ans += bit[j];
		for (int j = v[i]; j < n; j += j&-j) bit[j]++;
	}
	return ans;
}
```
