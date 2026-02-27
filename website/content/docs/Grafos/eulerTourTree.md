---
weight: 10
title: "Euler Tour Tree"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Mantem uma floresta enraizada dinamicamente

 e permite queries/updates em sub-arvore



 Chamar ETT E(n, v), passando n = numero de vertices

 e v = vector com os valores de cada vertice (se for vazio,

 constroi tudo com 0



 link(v, u) cria uma aresta de v pra u, de forma que u se torna

 o pai de v (eh preciso que v seja raiz anteriormente)

 cut(v) corta a resta de v para o pai

 query(v) retorna a soma dos valores da sub-arvore de v

 update(v, val) soma val em todos os vertices da sub-arvore de v

 update_v(v, val) muda o valor do vertice v para val

 is_in_subtree(v, u) responde se o vertice u esta na sub-arvore de v



 Tudo O(log(n)) com alta probabilidade



Link original: [eulerTourTree.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/eulerTourTree.cpp)

## Código
```cpp
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct ETT {
	// treap
	struct node {
		node *l, *r, *p;
		int pr, sz;
		T val, sub, lazy;
		int id;
		bool f; // se eh o 'first'
		int qt_f; // numero de firsts na subarvore
		node(int id_, T v, bool f_ = 0) : l(NULL), r(NULL), p(NULL), pr(rng()),
			sz(1), val(v), sub(v), lazy(), id(id_), f(f_), qt_f(f_) {}
		void prop() {
			if (lazy != T()) {
				if (f) val += lazy;
				sub += lazy*sz;
				if (l) l->lazy += lazy;
				if (r) r->lazy += lazy;
			}
			lazy = T();
		}
		void update() {
			sz = 1, sub = val, qt_f = f;
			if (l) l->prop(), sz += l->sz, sub += l->sub, qt_f += l->qt_f;
			if (r) r->prop(), sz += r->sz, sub += r->sub, qt_f += r->qt_f;
		}
	};

	node* root;

	int size(node* x) { return x ? x->sz : 0; }
	void join(node* l, node* r, node*& i) { // assume que l < r
		if (!l or !r) return void(i = l ? l : r);
		l->prop(), r->prop();
		if (l->pr > r->pr) join(l->r, r, l->r), l->r->p = i = l;
		else join(l, r->l, r->l), r->l->p = i = r;
		i->update();
	}
	void split(node* i, node*& l, node*& r, int v, int key = 0) {
		if (!i) return void(r = l = NULL);
		i->prop();
		if (key + size(i->l) < v) {
			split(i->r, i->r, r, v, key+size(i->l)+1), l = i;
			if (r) r->p = NULL;
			if (i->r) i->r->p = i;
		} else {
			split(i->l, l, i->l, v, key), r = i;
			if (l) l->p = NULL;
			if (i->l) i->l->p = i;
		}
		i->update();
	}
	int get_idx(node* i) {
		int ret = size(i->l);
		for (; i->p; i = i->p) {
			node* pai = i->p;
			if (i != pai->l) ret += size(pai->l) + 1;
		}
		return ret;
	}
	node* get_min(node* i) {
		if (!i) return NULL;
		return i->l ? get_min(i->l) : i;
	}
	node* get_max(node* i) {
		if (!i) return NULL;
		return i->r ? get_max(i->r) : i;
	}
	// fim da treap

	vector<node*> first, last;

	ETT(int n, vector<T> v = {}) : root(NULL), first(n), last(n) {
		if (!v.size()) v = vector<T>(n);
		for (int i = 0; i < n; i++) {
			first[i] = last[i] = new node(i, v[i], 1);
			join(root, first[i], root);
		}
	}
	ETT(const ETT& t) { throw logic_error("Nao copiar a ETT!"); }
	~ETT() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	pair<int, int> get_range(int i) {
		return {get_idx(first[i]), get_idx(last[i])};
	}
	void link(int v, int u) { // 'v' tem que ser raiz
		auto [lv, rv] = get_range(v);
		int ru = get_idx(last[u]);
		
		node* V;
		node *L, *M, *R;
		split(root, M, R, rv+1), split(M, L, M, lv);
		V = M;
		join(L, R, root);

		split(root, L, R, ru+1);
		join(L, V, L);
		join(L, last[u] = new node(u, T() /* elemento neutro */), L);
		join(L, R, root);
	}
	void cut(int v) {
		auto [l, r] = get_range(v);

		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		node *LL = get_max(L), *RR = get_min(R);
		if (LL and RR and LL->id == RR->id) { // remove duplicata
			 if (last[RR->id] == RR) last[RR->id] = LL;
			 node *A, *B;
			 split(R, A, B, 1);
			 delete A;
			 R = B;
		}
		join(L, R, root);
		join(root, M, root);
	}
	T query(int v) {
		auto [l, r] = get_range(v);
		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		T ans = M->sub;
		join(L, M, M), join(M, R, root);
		return ans;
	}
	void update(int v, T val) { // soma val em todo mundo da subarvore
		auto [l, r] = get_range(v);
		node *L, *M, *R;
		split(root, M, R, r+1), split(M, L, M, l);
		M->lazy += val;
		join(L, M, M), join(M, R, root);
	}
	void update_v(int v, T val) { // muda o valor de v pra val
		int l = get_idx(first[v]);
		node *L, *M, *R;
		split(root, M, R, l+1), split(M, L, M, l);
		M->val = M->sub = val;
		join(L, M, M), join(M, R, root);
	}
	bool is_in_subtree(int v, int u) { // se u ta na subtree de v
		auto [lv, rv] = get_range(v);
		auto [lu, ru] = get_range(u);
		return lv <= lu and ru <= rv;
	}

	void print(node* i) {
		if (!i) return;
		print(i->l);
		cout << i->id+1 << " ";
		print(i->r);
	}
	void print() { print(root); cout << endl; }
};
```
