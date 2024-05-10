---
weight: 10
title: "Distancia maxima entre dois pontos"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 max_dist2(v) - O(n log(n))

 max_dist_manhattan - O(n)



 Quadrado da Distancia Euclidiana (precisa copiar convex_hull, ccw e pt)

Link original: [maxDist.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/maxDist.cpp)

## Código
```cpp
ll max_dist2(vector<pt> v) { 
	v = convex_hull(v);
	if (v.size() <= 2) return dist2(v[0], v[1%v.size()]);
	ll ans = 0;
	int n = v.size(), j = 0;
	for (int i = 0; i < n; i++) {
		while (!ccw(v[(i+1)%n]-v[i], pt(0, 0), v[(j+1)%n]-v[j])) j = (j+1)%n;
		ans = max({ans, dist2(v[i], v[j]), dist2(v[(i+1)%n], v[j])});
	}
	return ans;
}

// Distancia de Manhattan
template<typename T> T max_dist_manhattan(vector<pair<T, T>> v) {
	T min_sum, max_sum, min_dif, max_dif;
	min_sum = max_sum = v[0].first + v[0].second;
	min_dif = max_dif = v[0].first - v[0].second;
	for (auto [x, y] : v) {
		min_sum = min(min_sum, x+y);
		max_sum = max(max_sum, x+y);
		min_dif = min(min_dif, x-y);
		max_dif = max(max_dif, x-y);
	}
	return max(max_sum - min_sum, max_dif - min_dif);
}
```
