---
weight: 10
title: "Heap Sort"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 O(n log n)



Link original: [heapSort.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/heapSort.cpp)

## Código
```cpp
void down(vector<int>& v, int n, int i) {
	while ((i = 2*i+1) < n) {
		if (i+1 < n and v[i] < v[i+1]) i++;
		if (v[i] < v[(i-1)/2]) break;
		swap(v[i], v[(i-1)/2]);
	}
}
void heap_sort(vector<int>& v) {
	int n = v.size();
	for (int i = n/2-1; i >= 0; i--) down(v, n, i);
	for (int i = n-1; i > 0; i--)
		swap(v[0], v[i]), down(v, i, 0);
}
```
