// Rooted Euler Tour Tree
//
// Mantem uma floresta enraizada dinamicamente
// e permite queries/updates em sub-arvore
//
// Chamar ETT E(n, w), passando n = numero de vertices
// e w = vector com os valores de cada vertice
//
// link(v, u) cria uma aresta de v pra u, de forma que u se torna
// o pai de v (eh preciso que v seja raiz anteriormente)
// cut(v) corta a resta de v para o pai
// get_root(v) retorna a raiz de v
// condense(v) remove v e faz seus filhos apontarem para pai(v)
// erase(v) remove v e corta suas arestas
// - Se usar condense ou erase, nao pode usar get_root!
// vtx_query e vtx_update operam sobre valor de um vertice
// subtree_query e subtree_update operam sobre sub-arvore
// is_ancestor(v, u) retorna se v eh ancestral de u
//
// Tudo O(log(n)) com alta probabilidade

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct rooted_ett {
	const static T ZERO = T();
	struct node {
		node *l, *r, *p;
		int pr, sz;
		T val, sub, lazy;
		int id; // id, ou -1 se nao eh first
		int qt_f; // numero de 'first' na subarvore
		node(T v, int id_) : l(NULL), r(NULL), p(NULL), pr(rng()),
			sz(1), val(v), sub(v), lazy(), id(id_), qt_f(id >= 0) {}
		void prop() {
			if (lazy != ZERO) {
				if (id >= 0) val += lazy;
				sub += lazy * qt_f;
				if (l) l->lazy += lazy;
				if (r) r->lazy += lazy;
			}
			lazy = ZERO;
		}
		void update() {
			sz = 1, sub = val, qt_f = id >= 0;
			if (l) l->prop(), sz += l->sz, sub += l->sub, qt_f += l->qt_f;
			if (r) r->prop(), sz += r->sz, sub += r->sub, qt_f += r->qt_f;
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

	vector<node*> first, last;

	rooted_ett(int n, vector<T> w) : first(n), last(n) {
		node* tmp;
		for (int i = 0; i < n; i++) {
			first[i] = new node(w[i], i);
			join(first[i], last[i] = new node(ZERO, -1), tmp);
		}
	}
	rooted_ett(const rooted_ett& t) { throw logic_error("Nao copiar a ETT!"); }
	~rooted_ett() {
		for (int i = 0; i < first.size(); i++) delete first[i], delete last[i];
	}

	tuple<node*, int, int> get_range(int i) {
		auto [root, l_idx] = get_idx(first[i]);
		return {root, l_idx, get_idx(last[i]).second};
	}
	tuple<node*, node*, node*> split3(node* root, int l, int r) {
		node *L, *M, *R;
		split(root, M, R, r+1);
		split(M, L, M, l);
		return {L, M, R};
	}
	node* extract_range(node*& root, int l, int r) {
		auto [L, M, R] = split3(root, l, r);
		join(L, R, root);
		return M;
	}
	void join3(node* L, node* M, node* R) {
		join(L, M, M), join(M, R, R);
	}

	void link(int v, int u) { // parent(v) <-- u
		auto [root_v, l, r] = get_range(v);
		root_v = extract_range(root_v, l, r);

		if (u == -1) return;

		auto [root, idx] = get_idx(first[u]);
		node *L, *R;
		split(root, L, R, idx+1);
		join3(L, root_v, R);
	}
	void cut(int v) { // corta de v pro pai
		link(v, -1);
	}
	int get_root(int v) {
		auto [root, idx] = get_idx(first[v]);
		while (root->l) root = root->l;
		return root->id;
	}

	// se usar condense ou erase, nao pode usar get_root!
	void condense(int v) { // remove v, pai dos filhos vira pai(v)
		auto [root, l, r] = get_range(v);
		auto E2 = extract_range(root, r, r);
		auto E1 = extract_range(root, l, l);
		join(E1, E2, E2);
	}
	void erase(int v) { // remove v e arestas adjacentes
		cut(v);
		condense(v);
	}

	T vtx_query(int v) {
		auto [root, idx] = get_idx(first[v]);
		auto [L, M, R] = split3(root, idx, idx);
		T ans = M->sub;
		join3(L, M, R);
		return ans;
	}
	void vtx_update(int v, T val) {
		auto [root, idx] = get_idx(first[v]);
		auto [L, M, R] = split3(root, idx, idx);
		M->lazy += val;
		M->prop();
		join3(L, M, R);
	}
	T subtree_query(int v) {
		auto [root, l, r] = get_range(v);
		auto [L, M, R] = split3(root, l, r);
		T ans = M->sub;
		join3(L, M, R);
		return ans;
	}
	void subtree_update(int v, T val) {
		auto [root, l, r] = get_range(v);
		auto [L, M, R] = split3(root, l, r);
		M->lazy += val;
		join3(L, M, R);
	}

	bool is_ancestor(int v, int u) { // se v eh ancestral de u
		auto [root_v, l_v, r_v] = get_range(v);
		auto [root_u, l_u, r_u] = get_range(u);
		return root_v == root_u and l_v <= l_u and r_u <= r_v;
	}
};
