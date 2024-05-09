---
weight: 10
title: "Split-Merge Set - Lazy"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Representa um conjunto de inteiros nao negativos

 Todas as operacoes custam O(log(N)),

 em que N = maior elemento do set,

 exceto o merge e o insert_range, que custa O(log(N)) amortizado

 Usa O(min(N, n log(N))) de memoria, sendo 'n' o

 numero de elementos distintos no set



Link original: [splitMergeSetLazy.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/splitMergeSetLazy.cpp)

## Código
```cpp
template<typename T> struct sms {
	struct node {
		node *l, *r;
		int cnt;
		bool flip;
		node() : l(NULL), r(NULL), cnt(0), flip(0) {}
		void update() {
			cnt = 0;
			if (l) cnt += l->cnt;
			if (r) cnt += r->cnt;
		}
	};

	void prop(node* x, int size) {
		if (!x or !x->flip) return;
		x->flip = 0;
		x->cnt = size - x->cnt;
		if (size > 1) {
			if (!x->l) x->l = new node();
			if (!x->r) x->r = new node();
			x->l->flip ^= 1;
			x->r->flip ^= 1;
		}
	}

	node* root;
	T N;

	sms() : root(NULL), N(0) {}
	sms(T v) : sms() { while (v >= N) N = 2*N+1; }
	sms(sms& t) : root(NULL), N(t.N) {
		for (int i = 0; i < t.size(); i++) insert(t[i]);
	}
	sms(initializer_list<T> v) : sms() { for (T i : v) insert(i); }
	void destroy(node* r) {
		vector<node*> q = {r};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}
	~sms() { destroy(root); }

	friend void swap(sms& a, sms& b) {
		swap(a.root, b.root), swap(a.N, b.N);
	}
	sms& operator =(const sms& v) {
		sms tmp = v;
		swap(tmp, *this);
		return *this;
	}
	int count(node* x, T size) {
		if (!x) return 0;
		prop(x, size);
		return x->cnt;
	}
	int size() { return count(root, N+1); }
	void clear() {
		sms tmp;
		swap(*this, tmp);
	}
	void expand(T v) {
		for (; N < v; N = 2*N+1) if (root) {
			prop(root, N+1);
			node* nroot = new node();
			nroot->l = root;
			root = nroot;
			root->update();
		}
	}

	node* insert(node* at, T idx, T l, T r) {
		if (!at) at = new node();
		else prop(at, r-l+1);
		if (l == r) {
			at->cnt = 1;
			return at;
		}
		T m = l + (r-l)/2;
		if (idx <= m) at->l = insert(at->l, idx, l, m);
		else at->r = insert(at->r, idx, m+1, r);
		return at->update(), at;
	}
	void insert(T v) {
		assert(v >= 0);
		expand(v);
		root = insert(root, v, 0, N);
	}

	node* erase(node* at, T idx, T l, T r) {
		if (!at) return at;
		prop(at, r-l+1);
		if (l == r) at->cnt = 0;
		else {
			T m = l + (r-l)/2;
			if (idx <= m) at->l = erase(at->l, idx, l, m);
			else at->r = erase(at->r, idx, m+1, r);
			at->update();
		}
		return at;
	}
	void erase(T v) {
		if (v < 0 or v > N) return;
		root = erase(root, v, 0, N);
	}

	int count(node* at, T a, T b, T l, T r) {
		if (!at or b < l or r < a) return 0;
		prop(at, r-l+1);
		if (a <= l and r <= b) return at->cnt;
		T m = l + (r-l)/2;
		return count(at->l, a, b, l, m) + count(at->r, a, b, m+1, r);
	}
	int count(T v) { return count(root, v, v, 0, N); }
	int order_of_key(T v) { return count(root, 0, v-1, 0, N); }
	int lower_bound(T v) { return order_of_key(v); }

	const T operator [](int i) { // i-esimo menor elemento
		assert(i >= 0 and i < size());
		node* at = root;
		T l = 0, r = N;
		while (l < r) {
			prop(at, r-l+1);
			T m = l + (r-l)/2;
			if (count(at->l, m-l+1) > i) at = at->l, r = m;
			else {
				i -= count(at->l, r-m);
				at = at->r; l = m+1;
			}
		}
		return l;
	}

	node* merge(node* a, node* b, T tam) {
		if (!a or !b) return a ? a : b;
		prop(a, tam), prop(b, tam);
		if (b->cnt == tam) swap(a, b);
		if (tam == 1 or a->cnt == tam) {
			destroy(b);
			return a;
		}
		a->l = merge(a->l, b->l, tam>>1), a->r = merge(a->r, b->r, tam>>1);
		a->update(), delete b;
		return a;
	}
	void merge(sms& s) { // mergeia dois sets
		if (N > s.N) swap(*this, s);
		expand(s.N);
		root = merge(root, s.root, N+1);
		s.root = NULL;
	}

	node* split(node*& x, int k, T tam) {
		if (k <= 0 or !x) return NULL;
		prop(x, tam);
		node* ret = new node();
		if (tam == 1) x->cnt = 0, ret->cnt = 1;
		else {
			if (k <= count(x->l, tam>>1)) ret->l = split(x->l, k, tam>>1);
			else {
				ret->r = split(x->r, k - count(x->l, tam>>1), tam>>1);
				swap(x->l, ret->l);
			}
			ret->update(), x->update();
		}
		return ret;
	}
	void split(int k, sms& s) { // pega os 'k' menores
		s.clear();
		s.root = split(root, min(k, size()), N+1);
		s.N = N;
	}
	// pega os menores que 'k'
	void split_val(T k, sms& s) { split(order_of_key(k), s); }

	void flip(node*& at, T a, T b, T l, T r) {
		if (!at) at = new node();
		else prop(at, r-l+1);
		if (a <= l and r <= b) {
			at->flip ^= 1;
			prop(at, r-l+1);
			return;
		}
		if (r < a or b < l) return;
		T m = l + (r-l)/2;
		flip(at->l, a, b, l, m), flip(at->r, a, b, m+1, r);
		at->update();
	}
	void flip(T l, T r) { // flipa os valores em [l, r]
		assert(l >= 0 and l <= r);
		expand(r);
		flip(root, l, r, 0, N);
	}
	// complemento considerando que o universo eh [0, lim]
	void complement(T lim) {
		assert(lim >= 0);
		if (lim > N) expand(lim);
		flip(root, 0, lim, 0, N);
		sms tmp;
		split_val(lim+1, tmp);
		swap(*this, tmp);
	}
	void insert_range(T l, T r) { // insere todo os valores em [l, r]
		sms tmp;
		tmp.flip(l, r);
		merge(tmp);
	}
};
```
