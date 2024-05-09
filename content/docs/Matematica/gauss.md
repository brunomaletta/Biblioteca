---
weight: 10
title: "Gauss"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Resolve sistema linear

 Retornar um par com o numero de solucoes

 e alguma solucao, caso exista



 O(n^2 * m)



Link original: [gauss.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/gauss.cpp)

## Código
```cpp
template<typename T>
pair<int, vector<T>> gauss(vector<vector<T>> a, vector<T> b) {
	const double eps = 1e-6;
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; i++) a[i].push_back(b[i]);

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m and row < n; col++) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
		if (abs(a[sel][col]) < eps) continue;
		for (int i = col; i <= m; i++)
			swap(a[sel][i], a[row][i]);
		where[col] = row;

		for (int i = 0; i < n; i++) if (i != row) {
			T c = a[i][col] / a[row][col];
			for (int j = col; j <= m; j++)
				a[i][j] -= a[row][j] * c;
		}
		row++;
	}

	vector<T> ans(m, 0);
	for (int i = 0; i < m; i++) if (where[i] != -1)
		ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i = 0; i < n; i++) {
		T sum = 0;
		for (int j = 0; j < m; j++)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m]) > eps)
			return pair(0, vector<T>());
	}

	for (int i = 0; i < m; i++) if (where[i] == -1)
		return pair(INF, ans);
	return pair(1, ans);
}
```
