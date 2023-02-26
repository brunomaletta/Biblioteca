// Suffix Array Dinamico
//
// Mantem o suffix array, lcp e rank de uma string,
// premitindo push_front e pop_front
// O operador [i] return um par com sa[i] e lcp[i]
// lcp[i] tem o lcp entre sa[i] e sa[i-1] (lcp[0] = 0)
//
// Complexidades:
// Construir sobre uma string de tamanho n: O(n log n)
// push_front e pop_front: O(log n) amortizado

struct dyn_sa {
	struct node {
		int sa, lcp;
		node *l, *r, *p;
		int sz, mi;
		node(int sa_, int lcp_, node* p_) : sa(sa_), lcp(lcp_),
			l(NULL), r(NULL), p(p_), sz(1), mi(lcp) {}
		void update() {
			sz = 1, mi = lcp;
			if (l) sz += l->sz, mi = min(mi, l->mi);
			if (r) sz += r->sz, mi = min(mi, r->mi);
		}
	};

	node* root;
	vector<ll> tag; // tag of a suffix (reversed id)
	string s; // reversed

	dyn_sa() : root(NULL) {}
	dyn_sa(string s_) : dyn_sa() {
		reverse(s_.begin(), s_.end());
		for (char c : s_) push_front(c);
	}
	~dyn_sa() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	int size(node* x) { return x ? x->sz : 0; }
	int mirror(int i) { return s.size()-1 - i; }
	bool cmp(int i, int j) {
		if (s[i] != s[j]) return s[i] < s[j];
		if (i == 0 or j == 0) return i < j;
		return tag[i-1] < tag[j-1];
	}
	void fix_path(node* x) { while (x) x->update(), x = x->p; }
	void flatten(vector<node*>& v, node* x) {
		if (!x) return;
		flatten(v, x->l);
		v.push_back(x);
		flatten(v, x->r);
	}
	void build(vector<node*>& v, node*& x, node* p, int L, int R, ll l, ll r) {
		if (L > R) return void(x = NULL);
		int M = (L+R)/2;
		ll m = (l+r)/2;
		x = v[M];
		x->p = p;
		tag[x->sa] = m;
		build(v, x->l, x, L, M-1, l, m-1), build(v, x->r, x, M+1, R, m+1, r);
		x->update();
	}
	void fix(node*& x, node* p, ll l, ll r) {
		if (3*max(size(x->l), size(x->r)) <= 2*size(x)) return x->update();
		vector<node*> v;
		flatten(v, x);
		build(v, x, p, 0, v.size()-1, l, r);
	}
	node* next(node* x) {
		if (x->r) {
			x = x->r;
			while (x->l) x = x->l;
			return x;
		}
		while (x->p and x->p->r == x) x = x->p;
		return x->p;
	}
	node* prev(node* x) {
		if (x->l) {
			x = x->l;
			while (x->r) x = x->r;
			return x;
		}
		while (x->p and x->p->l == x) x = x->p;
		return x->p;
	}

	int get_lcp(node* x, node* y) {
		if (!x or !y) return 0; // change defaut value here
		if (s[x->sa] != s[y->sa]) return 0;
		if (x->sa == 0 or y->sa == 0) return 1;
		return 1 + query(mirror(x->sa-1), mirror(y->sa-1));
	}
	void add_suf(node*& x, node* p, int id, ll l, ll r) {
		if (!x) {
			x = new node(id, 0, p);
			node *prv = prev(x), *nxt = next(x);
			int lcp_cur = get_lcp(prv, x), lcp_nxt = get_lcp(x, nxt);
			if (nxt) nxt->lcp = lcp_nxt, fix_path(nxt);
			x->lcp = lcp_cur;
			tag[id] = (l+r)/2;
			x->update();
			return;
		}
		if (cmp(id, x->sa)) add_suf(x->l, x, id, l, tag[x->sa]-1);
		else add_suf(x->r, x, id, tag[x->sa]+1, r);
		fix(x, p, l, r);
	}
	void push_front(char c) {
		s += c;
		tag.push_back(-1);
		add_suf(root, NULL, s.size() - 1, 0, 1e18);
	}

	void rem_suf(node*& x, int id) {
		if (x->sa != id) {
			if (tag[id] < tag[x->sa]) return rem_suf(x->l, id);
			return rem_suf(x->r, id);
		}
		node* nxt = next(x);
		if (nxt) nxt->lcp = min(nxt->lcp, x->lcp), fix_path(nxt);

		node *p = x->p, *tmp = x;
		if (!x->l or !x->r) {
			x = x->l ? x->l : x->r;
			if (x) x->p = p;
		} else {
			for (tmp = x->l, p = x; tmp->r; tmp = tmp->r) p = tmp;
			x->sa = tmp->sa, x->lcp = tmp->lcp;
			if (tmp->l) tmp->l->p = p;
			if (p->l == tmp) p->l = tmp->l;
			else p->r = tmp->l;
		}
		fix_path(p);
		delete tmp;
	}
	void pop_front() {
		if (!s.size()) return;
		s.pop_back();
		rem_suf(root, s.size());
		tag.pop_back();
	}
	
	int query(node* x, ll l, ll r, ll a, ll b) {
		if (!x or tag[x->sa] == -1 or r < a or b < l) return s.size();
		if (a <= l and r <= b) return x->mi;
		int ans = s.size();
		if (a <= tag[x->sa] and tag[x->sa] <= b) ans = min(ans, x->lcp);
		ans = min(ans, query(x->l, l, tag[x->sa]-1, a, b));
		ans = min(ans, query(x->r, tag[x->sa]+1, r, a, b));
		return ans;
	}
	int query(int i, int j) { // lcp(s[i..], s[j..])
		if (i == j) return s.size() - i;
		ll a = tag[mirror(i)], b = tag[mirror(j)];
		int ret = query(root, 0, 1e18, min(a, b)+1, max(a, b));
		return ret;
	}
	// optional: get rank[i], sa[i] and lcp[i]
	int rank(int i) {
		i = mirror(i);
		node* x = root;
		int ret = 0;
		while (x) {
			if (tag[x->sa] < tag[i]) {
				ret += size(x->l)+1;
				x = x->r;
			} else x = x->l;
		}
		return ret;
	}
	pair<int, int> operator[](int i) {
		node* x = root;
		while (1) {
			if (i < size(x->l)) x = x->l;
			else {
				i -= size(x->l);
				if (!i) return {mirror(x->sa), x->lcp};
				i--, x = x->r;
			}
		}
	}
};
