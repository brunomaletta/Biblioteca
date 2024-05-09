---
weight: 10
title: "Functional Graph"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 rt[i] fala o ID da raiz associada ao vertice i

 d[i] fala a profundidade (0 sse ta no ciclo)

 pos[i] fala a posicao de i no array que eh a concat. dos ciclos

 build(f, val) recebe a funcao f e o custo de ir de

 i para f[i] (por default, val = f)

 f_k(i, k) fala onde i vai parar se seguir k arestas

 path(i, k) fala o custo (soma) seguir k arestas a partir de i

 Se quiser outra operacao, da pra alterar facil o codigo

 Codigo um pouco louco, tenho que admitir



 build - O(n)

 f_k   - O(log(min(n, k)))

 path  - O(log(min(n, k)))



Link original: [functionalGraph.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/functionalGraph.cpp)

## Código
```cpp
namespace func_graph {
	int n;
	int f[MAX], vis[MAX], d[MAX];
	int p[MAX], pp[MAX], rt[MAX], pos[MAX];
	int sz[MAX], comp;
	vector<vector<int>> ciclo;
	ll val[MAX], jmp[MAX], seg[2*MAX];

	ll op(ll a, ll b) { return a+b; }; // mudar a operacao aqui
	void dfs(int i, int t = 2) {
		vis[i] = t;
		if (vis[f[i]] >= 2) { // comeca ciclo - f[i] eh o rep.
			d[i] = 0, rt[i] = comp;
			sz[comp] = t - vis[f[i]] + 1;
			p[i] = pp[i] = i, jmp[i] = val[i];
			ciclo.emplace_back();
			ciclo.back().push_back(i);
		} else {
			if (!vis[f[i]]) dfs(f[i], t+1);
			rt[i] = rt[f[i]];
			if (sz[comp]+1) { // to no ciclo
				d[i] = 0;
				p[i] = pp[i] = i, jmp[i] = val[i];
				ciclo.back().push_back(i);
			} else { // nao to no ciclo
				d[i] = d[f[i]]+1, p[i] = f[i];
				pp[i] = 2*d[pp[f[i]]] == d[pp[pp[f[i]]]]+d[f[i]] ? pp[pp[f[i]]] : f[i];
				jmp[i] = pp[i] == f[i] ? val[i] : op(val[i], op(jmp[f[i]], jmp[pp[f[i]]]));
			}
		}
		if (f[ciclo[rt[i]][0]] == i) comp++; // fim do ciclo
		vis[i] = 1;
	}
	void build(vector<int> f_, vector<int> val_ = {}) {
		n = f_.size(), comp = 0;
		if (!val_.size()) val_ = f_;
		for (int i = 0; i < n; i++)
			f[i] = f_[i], val[i] = val_[i], vis[i] = 0, sz[i] = -1;

		ciclo.clear();
		for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
		int t = 0;
		for (auto& c : ciclo) {
			reverse(c.begin(), c.end());
			for (int j : c) {
				pos[j] = t;
				seg[n+t] = val[j];
				t++;
			}
		}
		for (int i = n-1; i; i--) seg[i] = op(seg[2*i], seg[2*i+1]);
	}

	int f_k(int i, ll k) {
		while (d[i] and k) {
			int big = d[i] - d[pp[i]];
			if (big <= k) k -= big, i = pp[i];
			else k--, i = p[i];
		}
		if (!k) return i;
		return ciclo[rt[i]][(pos[i] - pos[ciclo[rt[i]][0]] + k) % sz[rt[i]]];
	}
	ll path(int i, ll k) {
		auto query = [&](int l, int r) {
			ll q = 0;
			for (l += n, r += n; l <= r; ++l/=2, --r/=2) {
				if (l%2 == 1) q = op(q, seg[l]);
				if (r%2 == 0) q = op(q, seg[r]);
			}
			return q;
		};
		ll ret = 0;
		while (d[i] and k) {
			int big = d[i] - d[pp[i]];
			if (big <= k) k -= big, ret = op(ret, jmp[i]), i = pp[i];
			else k--, ret = op(ret, val[i]), i = p[i];
		}
		if (!k) return ret;
		int first = pos[ciclo[rt[i]][0]], last = pos[ciclo[rt[i]].back()];

		// k/sz[rt[i]] voltas completas
		if (k/sz[rt[i]]) ret = op(ret, k/sz[rt[i]] * query(first, last));

		k %= sz[rt[i]];
		if (!k) return ret;
		int l = pos[i], r = first + (pos[i] - first + k - 1) % sz[rt[i]];
		if (l <= r) return op(ret, query(l, r));
		return op(ret, op(query(l, last), query(first, r)));
	}
}
```
