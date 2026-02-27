---
weight: 10
title: "Z"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 z[i] = lcp(s, s[i..n))



 Complexidades:

 z - O(|s|)

 match - O(|s| + |p|)



Link original: [z.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Strings/z.cpp)

## Código
```cpp
vector<int> get_z(string s) {
	int n = s.size();
	vector<int> z(n, 0);

	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}

	return z;
}
```
