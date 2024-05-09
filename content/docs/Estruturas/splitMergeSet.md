---
weight: 10
title: "Split-Merge Set"
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

 exceto o merge, que custa O(log(N)) amortizado

 Usa O(min(N, n log(N))) de memoria, sendo 'n' o

 numero de elementos distintos no set



Link original: [splitMergeSet.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/splitMergeSet.cpp)

## Código
```cpp
template<typename T, bool MULTI=false, typename SIZE_T=int> struct sms {
	struct node {
		node *l, *r;
		SIZE_T cnt;
		node() : l(NULL), r(NULL), cnt(0) {}
		void update() {
			cnt = 0;
			if (l) cnt += l->cnt;
			if (r) cnt += r->cnt;
		}
	};

	node* root;
	T N;

	sms() : root(NULL), N(0) {}
	sms(T v) : sms() { while (v >= N) N = 2*N+1; }
	sms(const sms& t) : root(NULL), N(t.N) {
		for (SIZE_T i = 0; i < t.size(); i++) {
			T at = t[i];
			SIZE_T qt = t.count(at);
			insert(at, qt);
			i += qt-1;
		}
	}
	sms(initializer_list<T> v) : sms() { for (T i : v) insert(i); }
	~sms() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	friend void swap(sms& a, sms& b) {
		swap(a.root, b.root), swap(a.N, b.N);
	}
	sms& operator =(const sms& v) {
		sms tmp = v;
		swap(tmp, *this);
		return *this;
	}
	SIZE_T size() const { return root ? root->cnt : 0; }
	SIZE_T count(node* x) const { return x ? x->cnt : 0; }
	void clear() {
		sms tmp;
		swap(*this, tmp);
	}
	void expand(T v) {
		for (; N < v; N = 2*N+1) if (root) {
			node* nroot = new node();
			nroot->l = root;
			root = nroot;
			root->update();
		}
	}

	node* insert(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) at = new node();
		if (l == r) {
			at->cnt += qt;
			if (!MULTI) at->cnt = 1;
			return at;
		}
		T m = l + (r-l)/2;
		if (idx <= m) at->l = insert(at->l, idx, qt, l, m);
		else at->r = insert(at->r, idx, qt, m+1, r);
		return at->update(), at;
	}
	void insert(T v, SIZE_T qt=1) { // insere 'qt' ocorrencias de 'v'
		if (qt <= 0) return erase(v, -qt);
		assert(v >= 0);
		expand(v);
		root = insert(root, v, qt, 0, N);
	}

	node* erase(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) return at;
		if (l == r) at->cnt = at->cnt < qt ? 0 : at->cnt - qt;
		else {
			T m = l + (r-l)/2;
			if (idx <= m) at->l = erase(at->l, idx, qt, l, m);
			else at->r = erase(at->r, idx, qt, m+1, r);
			at->update();
		}
		if (!at->cnt) delete at, at = NULL;
		return at;
	}
	void erase(T v, SIZE_T qt=1) { // remove 'qt' ocorrencias de 'v'
		if (v < 0 or v > N or !qt) return;
		if (qt < 0) insert(v, -qt);
		root = erase(root, v, qt, 0, N);
	}
	void erase_all(T v) { // remove todos os 'v'
		if (v < 0 or v > N) return;
		root = erase(root, v, numeric_limits<SIZE_T>::max(), 0, N);
	}

	SIZE_T count(node* at, T a, T b, T l, T r) const {
		if (!at or b < l or r < a) return 0;
		if (a <= l and r <= b) return at->cnt;
		T m = l + (r-l)/2;
		return count(at->l, a, b, l, m) + count(at->r, a, b, m+1, r);
	}
	SIZE_T count(T v) const { return count(root, v, v, 0, N); }
	SIZE_T order_of_key(T v) { return count(root, 0, v-1, 0, N); }
	SIZE_T lower_bound(T v) { return order_of_key(v); }

	const T operator [](SIZE_T i) const { // i-esimo menor elemento
		assert(i >= 0 and i < size());
		node* at = root;
		T l = 0, r = N;
		while (l < r) {
			T m = l + (r-l)/2;
			if (count(at->l) > i) at = at->l, r = m;
			else {
				i -= count(at->l);
				at = at->r; l = m+1;
			}
		}
		return l;
	}

	node* merge(node* l, node* r) {
		if (!l or !r) return l ? l : r;
		if (!l->l and !l->r) { // folha
			if (MULTI) l->cnt += r->cnt;
			delete r;
			return l;
		}
		l->l = merge(l->l, r->l), l->r = merge(l->r, r->r);
		l->update(), delete r;
		return l;
	}
	void merge(sms& s) { // mergeia dois sets
		if (N > s.N) swap(*this, s);
		expand(s.N);
		root = merge(root, s.root);
		s.root = NULL;
	}

	node* split(node*& x, SIZE_T k) {
		if (k <= 0 or !x) return NULL;
		node* ret = new node();
		if (!x->l and !x->r) x->cnt -= k, ret->cnt += k;
		else {
			if (k <= count(x->l)) ret->l = split(x->l, k);
			else {
				ret->r = split(x->r, k - count(x->l));
				swap(x->l, ret->l);
			}
			ret->update(), x->update();
		}
		if (!x->cnt) delete x, x = NULL;
		return ret;
	}
	void split(SIZE_T k, sms& s) { // pega os 'k' menores
		s.clear();
		s.root = split(root, min(k, size()));
		s.N = N;
	}
	// pega os menores que 'k'
	void split_val(T k, sms& s) { split(order_of_key(k), s); }
};
```
