// Splay Tree
//
// Todas as operacoes sao O(log(n)) amortizado
// Se quiser colocar mais informacao no node,
// mudar em 'update'

template<typename T> struct splaytree {
	struct node {
		node *ch[2], *p;
		int sz;
		T val;
		node(T v) {
			ch[0] = ch[1] = p = NULL;
			sz = 1;
			val = v;
		}
	};

	node* root;

	splaytree() { root = NULL; }
	~splaytree() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->ch[0]), q.push_back(x->ch[1]);
			delete x;
		}
	}

	void update(node* x) {
		x->sz = 1;
		for (int i = 0; i < 2; i++) if (x->ch[i]) {
			x->sz += x->ch[i]->sz;
		}
	}
	void rotate(node* x) { // x vai ficar em cima
		node *p = x->p, *pp = p->p;
		if (pp) pp->ch[pp->ch[1] == p] = x;
		bool d = p->ch[0] == x;
		p->ch[!d] = x->ch[d], x->ch[d] = p;
		if (p->ch[!d]) p->ch[!d]->p = p;
		x->p = pp, p->p = x;
		update(p), update(x);
	}
	node* splay(node* x) {
		if (!x) return x;
		root = x;
		while (x->p) {
			node *p = x->p, *pp = p->p;
			if (!pp) return rotate(x), x; // zig
			if ((pp->ch[0] == p)^(p->ch[0] == x))
				rotate(x), rotate(x); // zigzag
			else rotate(p), rotate(x); // zigzig
		}
		return x;
	}
	node* insert(T v, bool lb=0) {
		if (!root) return lb ? NULL : root = new node(v);
		node *x = root, *last = NULL;;
		while (1) {
			bool d = x->val < v;
			if (!d) last = x;
			if (x->val == v) break;
			if (x->ch[d]) x = x->ch[d];
			else {
				if (lb) break;
				x->ch[d] = new node(v);
				x->ch[d]->p = x;
				x = x->ch[d];
				break;
			}
		}
		splay(x);
		return lb ? splay(last) : x;
	}
	int size() { return root ? root->sz : 0; }
	int count(T v) { return insert(v, 1) and root->val == v; }
	node* lower_bound(T v) { return insert(v, 1); }
	void erase(T v) {
		if (!count(v)) return;
		node *x = root, *l = x->ch[0];
		if (!l) {
			root = x->ch[1];
			if (root) root->p = NULL;
			return delete x;
		}
		root = l, l->p = NULL;
		while (l->ch[1]) l = l->ch[1];
		splay(l);
		l->ch[1] = x->ch[1];
		if (l->ch[1]) l->ch[1]->p = l;
		delete x;
	}
	int order_of_key(T v) {
		if (!lower_bound(v)) return root ? root->sz : 0;
		return root->ch[0] ? root->ch[0]->sz : 0;
	}
	node* find_by_order(int k) {
		node* x = root;
		while (1) {
			if (x->ch[0] and x->ch[0]->sz >= k+1) x = x->ch[0];
			else {
				if (x->ch[0]) k -= x->ch[0]->sz;
				if (!k) return splay(x);
				if (!x->ch[1]) {
					splay(x);
					return NULL;
				}
				k--, x = x->ch[1];
			}
		}
	}
	T min() {
		node* x = root;
		while (x->ch[0]) x = x->ch[0]; // max -> ch[1]
		return splay(x)->val;
	}
};
