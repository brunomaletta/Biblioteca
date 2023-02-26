// Link-cut Tree - aresta
//
// Valores nas arestas
// rootify(v) torna v a raiz de sua arvore
// query(v, w) retorna a soma do caminho v--w
// update(v, w, x) soma x nas arestas do caminho v--w
//
// Todas as operacoes sao O(log(n)) amortizado

namespace lct {
	struct node {
		int p, ch[2];
		ll val, sub;
		bool rev;
		int sz, ar;
		ll lazy;
		node() {}
		node(int v, int ar_) :
		p(-1), val(v), sub(v), rev(0), sz(ar_), ar(ar_), lazy(0) {
			ch[0] = ch[1] = -1;
		}
	};

	node t[2*MAX]; // MAXN + MAXQ
	map<pair<int, int>, int> aresta;
	int sz;

	void prop(int x) {
		if (t[x].lazy) {
			if (t[x].ar) t[x].val += t[x].lazy;
			t[x].sub += t[x].lazy*t[x].sz;
			if (t[x].ch[0]+1) t[t[x].ch[0]].lazy += t[x].lazy;
			if (t[x].ch[1]+1) t[t[x].ch[1]].lazy += t[x].lazy;
		}
		if (t[x].rev) {
			swap(t[x].ch[0], t[x].ch[1]);
			if (t[x].ch[0]+1) t[t[x].ch[0]].rev ^= 1;
			if (t[x].ch[1]+1) t[t[x].ch[1]].rev ^= 1;
		}
		t[x].lazy = 0, t[x].rev = 0;
	}
	void update(int x) {
		t[x].sz = t[x].ar, t[x].sub = t[x].val;
		for (int i = 0; i < 2; i++) if (t[x].ch[i]+1) {
			prop(t[x].ch[i]);
			t[x].sz += t[t[x].ch[i]].sz;
			t[x].sub += t[t[x].ch[i]].sub;
		}
	}
	bool is_root(int x) {
		return t[x].p == -1 or (t[t[x].p].ch[0] != x and t[t[x].p].ch[1] != x);
	}
	void rotate(int x) {
		int p = t[x].p, pp = t[p].p;
		if (!is_root(p)) t[pp].ch[t[pp].ch[1] == p] = x;
		bool d = t[p].ch[0] == x;
		t[p].ch[!d] = t[x].ch[d], t[x].ch[d] = p;
		if (t[p].ch[!d]+1) t[t[p].ch[!d]].p = p;
		t[x].p = pp, t[p].p = x;
		update(p), update(x);
	}
	int splay(int x) {
		while (!is_root(x)) {
			int p = t[x].p, pp = t[p].p;
			if (!is_root(p)) prop(pp);
			prop(p), prop(x);
			if (!is_root(p)) rotate((t[pp].ch[0] == p)^(t[p].ch[0] == x) ? x : p);
			rotate(x);
		}
		return prop(x), x;
	}
	int access(int v) {
		int last = -1;
		for (int w = v; w+1; update(last = w), splay(v), w = t[v].p)
			splay(w), t[w].ch[1] = (last == -1 ? -1 : v);
		return last;
	}
	void make_tree(int v, int w=0, int ar=0) { t[v] = node(w, ar); }
	int find_root(int v) {
		access(v), prop(v);
		while (t[v].ch[0]+1) v = t[v].ch[0], prop(v);
		return splay(v);
	}
	bool conn(int v, int w) {
		access(v), access(w);
		return v == w ? true : t[v].p != -1;
	}
	void rootify(int v) {
		access(v);
		t[v].rev ^= 1;
	}
	ll query(int v, int w) {
		rootify(w), access(v);
		return t[v].sub;
	}
	void update(int v, int w, int x) {
		rootify(w), access(v);
		t[v].lazy += x;
	}
	void link_(int v, int w) {
		rootify(w);
		t[w].p = v;
	}
	void link(int v, int w, int x) { // v--w com peso x
		int id = MAX + sz++;
		aresta[make_pair(v, w)] = id;
		make_tree(id, x, 1);
		link_(v, id), link_(id, w);
	}
	void cut_(int v, int w) {
		rootify(w), access(v);
		t[v].ch[0] = t[t[v].ch[0]].p = -1;
	}
	void cut(int v, int w) {
		int id = aresta[make_pair(v, w)];
		cut_(v, id), cut_(id, w);
	}
	int lca(int v, int w) {
		access(v);
		return access(w);
	}
}
