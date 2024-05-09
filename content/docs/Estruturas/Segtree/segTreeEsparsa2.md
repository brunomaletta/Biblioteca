---
weight: 10
title: "SegTree Esparsa - O(q) memoria"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Query: min do range [a, b]

 Update: troca o valor de uma posicao

 Usa O(q) de memoria para q updates



 Complexidades:

 query - O(log(n))

 update - O(log(n))



Link original: [segTreeEsparsa2.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTreeEsparsa2.cpp)

## Código
```cpp
template<typename T> struct seg {
	struct node {
		node* ch[2];
		char d;
		T v;

		T mi;

		node(int d_, T v_, T val) : d(d_), v(v_) {
			ch[0] = ch[1] = NULL;
			mi = val;
		}
		node(node* x) : d(x->d), v(x->v), mi(x->mi) {
			ch[0] = x->ch[0], ch[1] = x->ch[1];
		}
		void update() {
			mi = numeric_limits<T>::max();
			for (int i = 0; i < 2; i++) if (ch[i])
				mi = min(mi, ch[i]->mi);
		}
	};

	node* root;
	char n;

	seg() : root(NULL), n(0) {}
	~seg() {
		std::vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->ch[0]), q.push_back(x->ch[1]);
			delete x;
		}
	}

	char msb(T v, char l, char r) { // msb in range (l, r]
		for (char i = r; i > l; i--) if (v>>i&1) return i;
		return -1;
	}
	void cut(node* at, T v, char i) {
		char d = msb(v ^ at->v, at->d, i);
		if (d == -1) return; // no need to split
		node* nxt = new node(at);
		at->ch[v>>d&1] = NULL;
		at->ch[!(v>>d&1)] = nxt;
		at->d = d;
	}

	node* update(node* at, T idx, T val, char i) {
		if (!at) return new node(-1, idx, val);
		cut(at, idx, i);
		if (at->d == -1) { // leaf
			at->mi = val;
			return at;
		}
		bool dir = idx>>at->d&1;
		at->ch[dir] = update(at->ch[dir], idx, val, at->d-1);
		at->update();
		return at;
	}
	void update(T idx, T val) {
		while (idx>>n) n++;
		root = update(root, idx, val, n-1);
	}

	T query(node* at, T a, T b, T l, T r, char i) {
		if (!at or b < l or r < a) return numeric_limits<T>::max();
		if (a <= l and r <= b) return at->mi;
		T m = l + (r-l)/2;
		if (at->d < i) {
			if ((at->v>>i&1) == 0) return query(at, a, b, l, m, i-1);
			else return query(at, a, b, m+1, r, i-1);
		}
		return min(query(at->ch[0], a, b, l, m, i-1), query(at->ch[1], a, b, m+1, r, i-1));
	}
	T query(T l, T r) { return query(root, l, r, 0, (T(1)<<n)-1, n-1); }
};
```
