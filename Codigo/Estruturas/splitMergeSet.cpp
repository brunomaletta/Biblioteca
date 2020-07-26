// Split-Merge Set
//
// Representa um conjunto de inteiros
// Todas as operacoes custam O(log(N)),
// em que N = maior elemento do set,
// exceto o merge, que custa O(log(N)) amortizado
// Usa O(n log(N)) de memoria, sendo 'n' o numero de
// elementos distintos no set

template<typename T, bool MULTI=false, typename SIZE_T=int> struct sms {
	struct node {
		node *l, *r;
		SIZE_T cnt;
		node() : l(NULL), r(NULL), cnt(0) {}
		void update() {
			cnt = 0;
			if (l) cnt += l->cnt;
			if (r) cnt += r->cnt;
		}
	};

	node* root;
	T N;

	sms() : root(NULL), N(0) {}
	sms(T v) : sms() {
		while (v >= N) N = 2*N+1;
	}
	sms(const sms& t) : root(NULL), N(t.N) {
		for (SIZE_T i = 0; i < t.size(); i++) {
			T at = t[i];
			SIZE_T qt = t.count(at);
			insert(at, qt);
			i += qt-1;
		}
	}
	sms(initializer_list<T> v) : sms() {
		for (T i : v) insert(i);
	}
	~sms() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	friend void swap(sms<T, MULTI, SIZE_T>& a, sms<T, MULTI, SIZE_T>& b) {
		swap(a.root, b.root), swap(a.N, b.N);
	}

	SIZE_T size() const { return root ? root->cnt : 0; }
	SIZE_T count(node* x) const { return x ? x->cnt : 0; }
	void clear() {
		sms<T, MULTI, SIZE_T> tmp;
		swap(*this, tmp);
	}

	node* insert(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) at = new node();
		if (l == r) {
			at->cnt += qt;
			if (!MULTI) at->cnt = 1;
			return at;
		}
		T m = l + (r-l)/2;
		if (idx <= m) at->l = insert(at->l, idx, qt, l, m);
		else at->r = insert(at->r, idx, qt, m+1, r);
		return at->update(), at;
	}
	void insert(T v, SIZE_T qt=1) { // insere 'qt' ocorrencias de 'v'
		if (qt <= 0) return erase(v, -qt);
		assert(v >= 0);
		while (v > N) {
			if (root) {
				node* nroot = new node();
				nroot->l = root;
				root = nroot;
				root->update();
			}
			N = 2*N+1;
		}
		root = insert(root, v, qt, 0, N);
	}

	node* erase(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) return at;
		if (l == r) at->cnt = qt == -1 ? 0 : max((SIZE_T)0, at->cnt - qt);
		else {
			T m = l + (r-l)/2;
			if (idx <= m) at->l = erase(at->l, idx, qt, l, m);
			else at->r = erase(at->r, idx, qt, m+1, r);
			at->update();
		}
		if (!at->cnt) {
			delete at;
			return NULL;
		}
		return at;
	}
	void erase(T v, SIZE_T qt=1) { // remove 'qt' ocorrencias de 'v'
		if (v < 0 or v > N or !qt) return;
		if (qt < 0) insert(v, -qt);
		root = erase(root, v, qt, 0, N);
	}
	void erase_all(T v) { // remove todos os 'v'
		if (v < 0 or v > N) return;
		root = erase(root, v, -1, 0, N);
	}

	void shrink() { // diminui o N em funcao do maior elemento no set
		while (root and !root->r) {
			node* at = root;
			root = root->l, N /= 2;
			delete at;
		}
	}

	SIZE_T count(node* at, T a, T b, T l, T r) const {
		if (!at or b < l or r < a) return 0;
		if (a <= l and r <= b) return at->cnt;
		T m = l + (r-l)/2;
		return count(at->l, a, b, l, m) + count(at->r, a, b, m+1, r);
	}
	SIZE_T count(T v) const { // quantas ocorrencias de 'v' tem no set
		if (v < 0 or v > N) return 0;
		return count(root, v, v, 0, N);
	}
	SIZE_T order_of_key(T v) { // quantos elementos < 'v' tem no set
		if (v <= 0) return 0;
		if (v > N) return size();
		return count(root, 0, v-1, 0, N);
	}
	// indice do primeiro elemento >= 'v' (ou size() se nao tem)
	SIZE_T lower_bound(T v) { return order_of_key(v); }

	const T operator [](SIZE_T i) const { // i-esimo menor elemento
		assert(i >= 0 and i < size());
		node* at = root;
		T l = 0, r = N;
		while (l < r) {
			T m = l + (r-l)/2;
			if (count(at->l) > i) at = at->l, r = m;
			else {
				i -= count(at->l);
				at = at->r; l = m+1;
			}
		}
		return l;
	}

	node* merge(node* l, node* r) {
		if (!l or !r) return l ? l : r;
		if (!l->l and !l->r) { // folha
			if (MULTI) l->cnt += r->cnt;
			delete r;
			return l;
		}
		l->l = merge(l->l, r->l), l->r = merge(l->r, r->r);
		l->update(), delete r;
		return l;
	}
	void merge(sms<T, MULTI, SIZE_T>& s) { // mergeia dos sets
		if (N > s.N) swap(*this, s);
		while (N < s.N) {
			if (root) {
				node* nroot = new node();
				nroot->l = root;
				root = nroot;
				root->update();
			}
			N = 2*N+1;
		}
		root = merge(root, s.root);
		s.root = NULL;
	}

	node* split(node*& x, SIZE_T k) {
		if (k <= 0 or !x) return NULL;
		node* ret = new node();
		if (!x->l and !x->r) { // folha
			x->cnt -= k;
			ret->cnt += k;
			if (!x->cnt) delete x, x = NULL;
			return ret;
		}
		int l = count(x->l);
		if (k <= l) ret->l = split(x->l, k);
		else {
			swap(x->l, ret->l);
			ret->r = split(x->r, k - l);
		}
		ret->update(), x->update();
		if (!x->cnt) delete x, x = NULL;
		return ret;
	}
	void split(SIZE_T k, sms<T, MULTI, SIZE_T>& s) { // os 'k' menores
		s.clear();
		s.root = split(root, min(k, size()));
		s.N = N;
	}
	void split_val(T k, sms<T, MULTI, SIZE_T>& s) { // os menores que 'k'
		split(order_of_key(k), s);
	}
};
