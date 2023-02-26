// SegTreap
//
// Muda uma posicao do plano, e faz query de operacao
// associativa e comutativa em retangulo
// Mudar ZERO e op
// Esparso nas duas coordenadas, inicialmente eh tudo ZERO
//
// Para query com distancia de manhattan <= d, faca
// nx = x+y, ny = x-y
// Update em (nx, ny), query em ((nx-d, ny-d), (nx+d, ny+d))
//
// Valores no X tem que ser de 0 ateh NX
// Para q operacoes, usa O(q log(NX)) de memoria, e as
// operacoes custa O(log(q) log(NX))

const int ZERO = INF;
const int op(int l, int r) { return min(l, r); }

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
	struct node {
		node *l, *r;
		int p;
		pair<ll, ll> idx; // {y, x}
		T val, mi;
		node(ll x, ll y, T val_) : l(NULL), r(NULL), p(rng()),
			idx(pair(y, x)), val(val_), mi(val) {}
		void update() {
			mi = val;
			if (l) mi = op(mi, l->mi);
			if (r) mi = op(mi, r->mi);
		}
	};

	node* root;

	treap() { root = NULL; }
	~treap() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}
	treap(treap&& t) : treap() { swap(root, t.root); }

	void join(node* l, node* r, node*& i) { // assume que l < r
		if (!l or !r) return void(i = l ? l : r);
		if (l->p > r->p) join(l->r, r, l->r), i = l;
		else join(l, r->l, r->l), i = r;
		i->update();
	}
	void split(node* i, node*& l, node*& r, pair<ll, ll> idx) {
		if (!i) return void(r = l = NULL);
		if (i->idx < idx) split(i->r, i->r, r, idx), l = i;
		else split(i->l, l, i->l, idx), r = i;
		i->update();
	}
	void update(ll x, ll y, T v) {
		node *L, *M, *R;
		split(root, M, R, pair(y, x+1)), split(M, L, M, pair(y, x));
		if (M) M->val = M->mi = v;
		else M = new node(x, y, v);
		join(L, M, M), join(M, R, root);
	}
	T query(ll ly, ll ry) {
		node *L, *M, *R;
		split(root, M, R, pair(ry, LINF)), split(M, L, M, pair(ly, 0));
		T ret = M ? M->mi : ZERO;
		join(L, M, M), join(M, R, root);
		return ret;
	}
};

template<typename T> struct segtreap {
	vector<treap<T>> seg;
	vector<int> ch[2];
	ll NX;

	segtreap(ll NX_) : seg(1), NX(NX_) { ch[0].push_back(-1), ch[1].push_back(-1); }

	int get_ch(int i, int d){
		if (ch[d][i] == -1) {
			ch[d][i] = seg.size();
			seg.emplace_back();
			ch[0].push_back(-1), ch[1].push_back(-1);
		}
		return ch[d][i];
	}

	T query(ll lx, ll rx, ll ly, ll ry, int p, ll l, ll r) {
		if (rx < l or r < lx) return ZERO;
		if (lx <= l and r <= rx) return seg[p].query(ly, ry);

		ll m = l + (r-l)/2;
		return op(query(lx, rx, ly, ry, get_ch(p, 0), l, m),
				query(lx, rx, ly, ry, get_ch(p, 1), m+1, r));
	}
	T query(ll lx, ll rx, ll ly, ll ry) { return query(lx, rx, ly, ry, 0, 0, NX); }

	void update(ll x, ll y, T val, int p, ll l, ll r) {
		if (l == r) return seg[p].update(x, y, val);
		ll m = l + (r-l)/2;
		if (x <= m) update(x, y, val, get_ch(p, 0), l, m);
		else update(x, y, val, get_ch(p, 1), m+1, r);
		seg[p].update(x, y, val);
	}
	void update(ll x, ll y, T val) { update(x, y, val, 0, 0, NX); }
};
