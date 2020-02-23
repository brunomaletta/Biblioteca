// Link-Cut Tree
//
// Valores nas arestas
// make_tree(v, w) cria uma nova arvore com um
// vertice soh com valor 'w'
// rootify(v) torna v a raiz de sua arvore
// query(v, w) retorna a soma do caminho v--w
// update(v, w, x) soma x nas arestas do caminho v--w
//
// Todas as operacoes sao O(log(n)) amortizado

namespace lct {
	struct node {
		int p, path_p, ch[2];
		ll val, sub;
		bool rev;
		int sz, ar;
		ll lazy;
		node() {}
		node(int v, int ar_) :
		p(-1), path_p(-1), val(v), sub(v), rev(0), sz(ar_), ar(ar_), lazy(0) {
			ch[0] = ch[1] = -1;
		}
	};

	node t[2*MAX]; // MAXN + MAXQ
	map<ii, int> aresta;

	void prop(int x) {
		if (t[x].lazy) {
			if (t[x].ar) t[x].val += t[x].lazy, t[x].sub += t[x].lazy*t[x].sz;
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
	void rotate(int x) {
		int p = t[x].p, pp = t[p].p;
		if (pp+1) t[pp].ch[t[pp].ch[1] == p] = x;
		bool d = t[p].ch[0] == x;
		t[p].ch[!d] = t[x].ch[d], t[x].ch[d] = p;
		if (t[p].ch[!d]+1) t[t[p].ch[!d]].p = p;
		t[x].p = pp, t[p].p = x;
		t[x].path_p = t[p].path_p, t[p].path_p = -1;
		update(p), update(x);
	}
	int splay(int x) {
		int r = x;
		vector<int> st = {r};
		while (t[r].p+1) st.push_back(r = t[r].p);
		while (st.size()) prop(st.back()), st.pop_back();
		while (t[x].p+1) {
			int p = t[x].p, pp = t[p].p;
			if (pp == -1) return rotate(x), x;
			if ((t[pp].ch[0] == p)^(t[p].ch[0] == x))
				rotate(x), rotate(x);
			else rotate(p), rotate(x);
		}
		return x;
	}
	int access(int v) {
		splay(v);
		if (t[v].ch[1]+1) {
			t[t[v].ch[1]].path_p = v;
			t[v].ch[1] = t[t[v].ch[1]].p = -1;
			update(v);
		}
		int last = v;
		for (int w; (w=t[v].path_p)+1; update(w), splay(v)) {
			splay(last = w);
			if (t[w].ch[1]+1) {
				t[t[w].ch[1]].path_p = w;
				t[t[w].ch[1]].p = -1;
			}
			t[w].ch[1] = v, t[v].p = w;
		}
		return last;
	}
	void make_tree(int v, int w=0, int ar=0) { t[v] = node(w, ar); }
	int find_root(int v) {
		access(v);
		while (t[v].ch[0]+1) v = t[v].ch[0];
		return splay(v);
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
		t[v].lazy = x;
	}
	void link_(int v, int w) {
		rootify(v), access(w);
		t[w].ch[1] = v, t[v].p = w;
		update(w);
	}
	void link(int v, int w, int x) { // v--w com peso x
		int id = MAX + aresta.size();
		aresta[make_pair(v, w)] = id;
		make_tree(id, x, 1);
		link_(v, id), link_(id, w);
	}
	void cut_(int v, int w) {
		rootify(w), access(v);
		t[v].ch[0] = t[t[v].ch[0]].p = -1;
		update(v);
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
