// Treap Persistent Implicita
//
// Todas as operacoes custam
// O(log(n)) com alta probabilidade

mt19937_64 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct node {
	node *l, *r;
	ll sz, val, sub;
	node(ll v) : l(NULL), r(NULL), sz(1), val(v), sub(v) {}
	node(node* x) : l(x->l), r(x->r), sz(x->sz), val(x->val), sub(x->sub) {}
	void update() {
		sz = 1, sub = val;
		if (l) sz += l->sz, sub += l->sub;
		if (r) sz += r->sz, sub += r->sub;
		sub %= MOD;
	}
};

ll size(node* x) { return x ? x->sz : 0; }
void update(node* x) { if (x) x->update(); }
node* copy(node* x) { return x ? new node(x) : NULL; }

node* join(node* l, node* r) {
	if (!l or !r) return l ? copy(l) : copy(r);
	node* ret;
	if (rng() % (size(l) + size(r)) < size(l)) {
		ret = copy(l);
		ret->r = join(ret->r, r);
	} else {
		ret = copy(r);
		ret->l = join(l, ret->l);
	}
	return update(ret), ret;
}

void split(node* x, node*& l, node*& r, ll v, ll key = 0) {
	if (!x) return void(l = r = NULL);
	if (key + size(x->l) < v) {
		l = copy(x);
		split(l->r, l->r, r, v, key+size(l->l)+1);
	} else {
		r = copy(x);
		split(r->l, l, r->l, v, key);
	}
	update(l), update(r);
}

vector<node*> treap;

void init(const vector<ll>& v) {
	treap = {NULL};
	for (auto i : v) treap[0] = join(treap[0], new node(i));
}
