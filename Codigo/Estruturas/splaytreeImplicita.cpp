// Splay Tree Implicita
//
// vector da NASA
// Um pouco mais rapido q a treap
// O construtor a partir do vector
// eh linear, todas as outras operacoes
// custam O(log(n)) amortizado

template<typename T> struct splay {
	struct node {
		node *ch[2], *p;
		int sz;
		T val, sub, lazy;
		bool rev;
		node(T v) {
			ch[0] = ch[1] = p = NULL;
			sz = 1;
			sub = val = v;
			lazy = 0;
			rev = false;
		}
		void prop() {
			if (lazy) {
				val += lazy, sub += lazy*sz;
				if (ch[0]) ch[0]->lazy += lazy;
				if (ch[1]) ch[1]->lazy += lazy;
			}
			if (rev) {
				swap(ch[0], ch[1]);
				if (ch[0]) ch[0]->rev ^= 1;
				if (ch[1]) ch[1]->rev ^= 1;
			}
			lazy = 0, rev = 0;
		}
		void update() {
			sz = 1, sub = val;
			for (int i = 0; i < 2; i++) if (ch[i]) {
				ch[i]->prop();
				sz += ch[i]->sz;
				sub += ch[i]->sub;
			}
		}
	};

	node* root;

	splay() { root = NULL; }
	splay(node* x) {
		root = x;
		if (root) root->p = NULL;
	}
	splay(vector<T> v) { // O(n)
		root = NULL;
		for (T i : v) {
			node* x = new node(i);
			x->ch[0] = root;
			if (root) root->p = x;
			root = x;
			root->update();
		}
	}
	splay(const splay& t) {
		throw logic_error("Nao copiar a splay!");
	}
	~splay() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->ch[0]), q.push_back(x->ch[1]);
			delete x;
		}
	}

	int size(node* x) { return x ? x->sz : 0; }
	void rotate(node* x) { // x vai ficar em cima
		node *p = x->p, *pp = p->p;
		if (pp) pp->ch[pp->ch[1] == p] = x;
		bool d = p->ch[0] == x;
		p->ch[!d] = x->ch[d], x->ch[d] = p;
		if (p->ch[!d]) p->ch[!d]->p = p;
		x->p = pp, p->p = x;
		p->update(), x->update();
	}
	node* splaya(node* x) {
		if (!x) return x;
		root = x, x->update();
		while (x->p) {
			node *p = x->p, *pp = p->p;
			if (!pp) return rotate(x), x; // zig
			if ((pp->ch[0] == p)^(p->ch[0] == x))
				rotate(x), rotate(x); // zigzag
			else rotate(p), rotate(x); // zigzig
		}
		return x;
	}
	node* find(int v) {
		if (!root) return NULL;
		node *x = root;
		int key = 0;
		while (1) {
			x->prop();
			bool d = key + size(x->ch[0]) < v;
			if (key + size(x->ch[0]) != v and x->ch[d]) {
				if (d) key += size(x->ch[0])+1;
				x = x->ch[d];
			} else break;
		}
		return splaya(x);
	}
	int size() { return root ? root->sz : 0; }
	void join(splay<T>& l) { // assume que l < *this
		if (!size()) swap(root, l.root);
		if (!size() or !l.size()) return;
		node* x = l.root;
		while (1) {
			x->prop();
			if (!x->ch[1]) break;
			x = x->ch[1];
		}
		l.splaya(x), root->prop(), root->update();
		x->ch[1] = root, x->ch[1]->p = x;
		root = l.root, l.root = NULL;
		root->update();
	}
	node* split(int v) { // retorna os elementos < v
		if (v <= 0) return NULL;
		if (v >= size()) {
			node* ret = root;
			root = NULL;
			ret->update();
			return ret;
		}
		find(v);
		node* l = root->ch[0];
		root->ch[0] = NULL;
		if (l) l->p = NULL;
		root->update();
		return l;
	}
	T& operator [](int i) {
		find(i);
		return root->val;
	}
	void push_back(T v) { // O(1)
		node* r = new node(v);
		r->ch[0] = root;
		if (root) root->p = r;
		root = r, root->update();
	}
	T query(int l, int r) {
		splay<T> M(split(r+1));
		splay<T> L(M.split(l));
		T ans = M.root->sub;
		M.join(L), join(M);
		return ans;
	}
	void update(int l, int r, T s) {
		splay<T> M(split(r+1));
		splay<T> L(M.split(l));
		M.root->lazy += s;
		M.join(L), join(M);
	}
	void reverse(int l, int r) {
		splay<T> M(split(r+1));
		splay<T> L(M.split(l));
		M.root->rev ^= 1;
		M.join(L), join(M);
	}
	void erase(int l, int r) {
		splay<T> M(split(r+1));
		splay<T> L(M.split(l));
		join(L);
	}
};
