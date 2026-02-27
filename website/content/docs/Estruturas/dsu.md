---
weight: 10
title: "DSU"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Une dois conjuntos e acha a qual conjunto um elemento pertence por seu id



 find e unite: O(a(n)) ~= O(1) amortizado



Link original: [dsu.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/dsu.cpp)

## Código
```cpp
struct dsu {
	vector<int> id, sz;

	dsu(int n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }

	int find(int a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a;
	}
};

// DSU de bipartido
//
// Une dois vertices e acha a qual componente um vertice pertence
// Informa se a componente de um vertice e bipartida
//
// find e unite: O(log(n))

struct dsu {
	vector<int> id, sz, bip, c;

	dsu(int n) : id(n), sz(n, 1), bip(n, 1), c(n) { 
		iota(id.begin(), id.end(), 0); 
	}

	int find(int a) { return a == id[a] ? a : find(id[a]); }
	int color(int a) { return a == id[a] ? c[a] : c[a] ^ color(id[a]); }

	void unite(int a, int b) {
		bool change = color(a) == color(b);
		a = find(a), b = find(b);
		if (a == b) {
			if (change) bip[a] = 0;
			return;
		}
		
		if (sz[a] < sz[b]) swap(a, b);
		if (change) c[b] = 1;
		sz[a] += sz[b], id[b] = a, bip[a] &= bip[b];
	}
};


// DSU Persistente
//
// Persistencia parcial, ou seja, tem que ir
// incrementando o 't' no une
//
// find e unite: O(log(n))

struct dsu {
	vector<int> id, sz, ti;

	dsu(int n) : id(n), sz(n, 1), ti(n, -INF) { 
		iota(id.begin(), id.end(), 0); 
	}

	int find(int a, int t) { 
		if (id[a] == a or ti[a] > t) return a;
		return find(id[a], t);
	}

	void unite(int a, int b, int t) {
		a = find(a, t), b = find(b, t);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b], id[b] = a, ti[b] = t;
	}
};

// DSU com rollback
//
// checkpoint(): salva o estado atual de todas as variaveis
// rollback(): retorna para o valor das variaveis para 
// o ultimo checkpoint
//
// Sempre que uma variavel muda de valor, adiciona na stack
//
// find e unite: O(log(n))
// checkpoint: O(1)
// rollback: O(m) em que m e o numero de vezes que alguma
// variavel mudou de valor desde o ultimo checkpoint

struct dsu {
	vector<int> id, sz;
	stack<stack<pair<int&, int>>> st;

	dsu(int n) : id(n), sz(n, 1) { 
		iota(id.begin(), id.end(), 0), st.emplace(); 
	}
		
	void save(int &x) { st.top().emplace(x, x); }

	void checkpoint() { st.emplace(); }
	
	void rollback() {
		while(st.top().size()) {
			auto [end, val] = st.top().top(); st.top().pop();
			end = val;
		}
		st.pop();
	}

	int find(int a) { return a == id[a] ? a : find(id[a]); }

	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		save(sz[a]), save(id[b]);
		sz[a] += sz[b], id[b] = a;
	}
};
```
