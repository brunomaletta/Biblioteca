// Unrooted Euler Tour Tree
//
// Mantem uma floresta dinamicamente
// e permite queries/updates em componentes
//
// Chamar ETT E(n, w), passando n = numero de vertices
// e w = vector com os valores de cada vertice
//
// link(v, u) cria uma aresta entre v e u 
// cut(v, u)  corta aresta entre v e u
// get_root(v) retorna a raiz de v
// branc_query(v, u) e branch_update(v, u) operam sobre o componente
// conexo de v se arestas {v, u} fosse removida do grafo
// comp_query(v) e comp_update(v, val) operam sobre o compoente conexo de v
// point_update(v, val) atualiza o valor do vertice v
// point_update(v, val, u) atualiza o valor da aresta {v, u}
//
// Tudo O(log(n)) com alta probabilidade

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct unrooted_ett {
	const static T ZERO = T();
	struct node {
		node *l, *r, *p;
		bool is_vtx;
		int pr, sz, vtx_cnt;
		T val, sub, lazy;
		node(T v, bool is_vtx_ = false) : l(NULL), r(NULL), p(NULL), is_vtx(is_vtx_),
			pr(rng()), sz(1), vtx_cnt(is_vtx), val(v), sub(v), lazy(ZERO) {}
		void prop() {
			if (lazy != ZERO) {
				if (is_vtx) val += lazy;
				sub += lazy * vtx_cnt;
				if (l) l->lazy += lazy;
				if (r) r->lazy += lazy;
			}
			lazy = ZERO;
		}
		void update() {
			sz = 1, vtx_cnt = is_vtx, sub = val;
			for (auto& i : {l, r}) if (i) {
				i->prop();
				sz += i->sz, vtx_cnt += i->vtx_cnt;
				sub += i->sub;
			}
		}
	};

	int size(node* x) { return x ? x->sz : 0; }
	void join(node* l, node* r, node*& i) {
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
	pair<node*, int> get_idx(node* i) { // {root, idx}
		int ret = size(i->l);
		for (; i->p; i = i->p) if (i != i->p->l)
			ret += size(i->p->l) + 1;
		i->prop();
		return {i, ret};
	}

	// as treaps sao disjuntas!
	map<pair<int, int>, node*> mp;

	unrooted_ett(int n, const vector<T>& w) { // w = valor de cada vertice
		for (int i = 0; i < n; i++) mp[pair(i, i)] = new node(w[i], true);
	}
	unrooted_ett(const unrooted_ett& t) { throw logic_error("Nao copiar a ETT!"); }
	~unrooted_ett() { for (auto [__, ptr] : mp) delete ptr; }

	void link(int v, int u, T val = ZERO) {
		auto [root_v, idx_v] = get_idx(mp[pair(v, v)]);
		node *L_v, *R_v;
		split(root_v, L_v, R_v, idx_v);
		join(R_v, L_v, root_v);

		auto [root, idx] = get_idx(mp[pair(u, u)]);
		node *L, *R;
		split(root, L, R, idx);
		join(L, mp[pair(u, v)] = new node(val), L); // w[(u, v)]
		join(L, root_v, L);
		join(L, mp[pair(v, u)] = new node(ZERO), L); // w[(v, u)]
		join(L, R, R);
	}
	node* cut(int v, int u) { // retorna a raiz de v
		auto [root, l] = get_idx(mp[pair(u, v)]);
		int r = get_idx(mp[pair(v, u)]).second;
		bool rev = false;
		if (l > r) swap(l, r), rev = true;

		node *L, *E1, *M, *E2, *R;
		split(root, E2, R, r+1);
		split(E2, M, E2, r);
		split(M, E1, M, l+1);
		split(E1, L, E1, l);

		delete E1;
		delete E2;
		mp.erase(pair(v, u));
		mp.erase(pair(u, v));

		join(L, R, R);

		return rev ? R : M;
	}

	// opera sobre component(v) em F \ {v, u}
	T branch_query(int v, int u) {
		auto root = cut(v, u);
		T ret = root->sub;
		link(v, u);
		return ret;
	}
	void branch_update(int v, int u, T val) {
		auto root = cut(v, u);
		root->lazy += val;
		link(v, u);
	}

	// opera sobre component(v)
	T comp_query(int v) {
		auto root = get_idx(mp[pair(v, v)]).first;
		return root->sub;
	}
	void comp_update(int v, T val) {
		auto root = get_idx(mp[pair(v, v)]).first;
		root->lazy += val;
	}

	// w[v] += val, ou w[(v, u)] += val
	void point_update(int v, T val, int u = -1) {
		if (u == -1) u = v;
		auto [root, idx] = get_idx(mp[pair(v, u)]);

		node *L, *M, *R;
		split(root, M, R, idx+1);
		split(M, L, M, idx);

		M->lazy += val;

		join(L, M, M);
		join(M, R, R);
	}
};
