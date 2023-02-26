// Conectividade Dinamica LCT
//
// Offline com link-cut trees
// O(n log(n))

namespace lct {
	struct node {
		int p, ch[2];
		int val, sub;
		bool rev;
		node() {}
		node(int v) : p(-1), val(v), sub(v), rev(0) { ch[0] = ch[1] = -1; }
	};
 
	node t[2*MAX]; // MAXN + MAXQ
	map<pair<int, int>, int> aresta;
	int sz;
 
	void prop(int x) {
		if (t[x].rev) {
			swap(t[x].ch[0], t[x].ch[1]);
			if (t[x].ch[0]+1) t[t[x].ch[0]].rev ^= 1;
			if (t[x].ch[1]+1) t[t[x].ch[1]].rev ^= 1;
		}
		t[x].rev = 0;
	}
	void update(int x) {
		t[x].sub = t[x].val;
		for (int i = 0; i < 2; i++) if (t[x].ch[i]+1) {
			prop(t[x].ch[i]);
			t[x].sub = min(t[x].sub, t[t[x].ch[i]].sub);
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
	void make_tree(int v, int w=INF) { t[v] = node(w); }
	bool conn(int v, int w) {
		access(v), access(w);
		return v == w ? true : t[v].p != -1;
	}
	void rootify(int v) {
		access(v);
		t[v].rev ^= 1;
	}
	int query(int v, int w) {
		rootify(w), access(v);
		return t[v].sub;
	}
	void link_(int v, int w) {
		rootify(w);
		t[w].p = v;
	}
	void link(int v, int w, int x) { // v--w com peso x
		int id = MAX + sz++;
		aresta[make_pair(v, w)] = id;
		make_tree(id, x);
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
}

void dyn_conn() {
	int n, q; cin >> n >> q;
	vector<int> p(2*q, -1); // outra ponta do intervalo
	for (int i = 0; i < n; i++) lct::make_tree(i);
	vector<pair<int, int>> qu(q);
	map<pair<int, int>, int> m;
	for (int i = 0; i < q; i++) {
		char c; cin >> c;
		if (c == '?') continue;
		int a, b; cin >> a >> b; a--, b--;
		if (a > b) swap(a, b);
		qu[i] = {a, b};
		if (c == '+') {
			p[i] = i+q, p[i+q] = i;
			m[make_pair(a, b)] = i;
		} else {
			int j = m[make_pair(a, b)];
			p[i] = j, p[j] = i;
		}
	}
	int ans = n;
	for (int i = 0; i < q; i++) {
		if (p[i] == -1) {
			cout << ans << endl; // numero de comp conexos
			continue;
		}
		int a = qu[i].first, b = qu[i].second;
		if (p[i] > i) { // +
			if (lct::conn(a, b)) {
				int mi = lct::query(a, b);
				if (p[i] < mi) {
					p[p[i]] = p[i];
					continue;
				}
				lct::cut(qu[p[mi]].first, qu[p[mi]].second), ans++;
				p[mi] = mi;
			}
			lct::link(a, b, p[i]), ans--;
		} else if (p[i] != i) lct::cut(a, b), ans++; // -
	}
}
