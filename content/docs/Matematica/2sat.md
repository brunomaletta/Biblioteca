---
weight: 10
title: "2-SAT"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 solve() retorna um par, o first fala se eh possivel

 atribuir, o second fala se cada variavel eh verdadeira



 O(|V|+|E|) = O(#variaveis + #restricoes)



Link original: [2sat.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Matematica/2sat.cpp)

## Código
```cpp
struct sat {
	int n, tot;
	vector<vector<int>> g;
	vector<int> vis, comp, id, ans;
	stack<int> s;

	sat() {}
	sat(int n_) : n(n_), tot(n), g(2*n) {}

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if ((u>>1) < n and ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}
	void add_cl(int x, int y) { // x ou y
		add_impl(~x, y);
	}
	void add_xor(int x, int y) { // x xor y
		add_cl(x, y), add_cl(~x, ~y);
	}
	void add_eq(int x, int y) { // x = y
		add_xor(~x, y);
	}
	void add_true(int x) { // x = T
		add_impl(~x, x);
	}
	void at_most_one(vector<int> v) { // no max um verdadeiro
		g.resize(2*(tot+v.size()));
		for (int i = 0; i < v.size(); i++) {
			add_impl(tot+i, ~v[i]);
			if (i) {
				add_impl(tot+i, tot+i-1);
				add_impl(v[i], tot+i-1);
			}
		}
		tot += v.size();
	}

	pair<bool, vector<int>> solve() {
		ans = vector<int>(n, -1);
		int t = 0;
		vis = comp = id = vector<int>(2*tot, 0);
		for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
		for (int i = 0; i < tot; i++)
			if (comp[2*i] == comp[2*i+1]) return {false, {}};
		return {true, ans};
	}
};
```
