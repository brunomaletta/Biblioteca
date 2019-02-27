// Complexidades:
//
// insert - O(log(n))
// erase - O(log(n))
// query - O(log(n))

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
	struct node {
		int p;
		int l, r;
		T v;
		int sz;
		T min_s;
		node(){}
		node(T v):p(rng()), l(-1), r(-1), v(v){}
	} t[MAX];
	int size(int i){
		if (i == -1) return 0;
		return t[i].sz;
	}
	void update(int i){
		if (i == -1) return;
		t[i].min_s = t[i].v;

		int l = t[i].l;
		int r = t[i].r;
		t[i].sz = 1 + size(l) + size(r);

		if (l != -1)
			t[i].min_s = min(t[i].min_s, t[l].min_s);
		if (r != -1)
			t[i].min_s = min(t[i].min_s, t[r].min_s);
	}	
	void split(int i, int k, int &l, int &r){ //key
		if (i == -1){
			l = -1; r = -1;
			return;
		}
		if (t[i].v < k){
			split(t[i].r, k, l, r);
			t[i].r = l;
			l = i;
		}
		else{
			split(t[i].l, k, l, r);
			t[i].l = r;
			r = i;
		}
		update(i);
	}
	void split_implicit(int i, int k, int &l, int &r, int sz = 0){
		if (i == -1){
			l = -1; r = -1;
			return;
		}
		int inc = size(t[i].l); //quantidade elementos menor que k
		if (sz+inc < k){
			split_implicit(t[i].r, k, l, r, sz+inc+1);
			t[i].r = l;
			l = i;
		}
		else{
			split_implicit(t[i].l, k, l, r, sz);
			t[i].l = r;
			r = i;
		}
		update(i);
	}
	int merge(int l, int r){ //priority
		if (l == -1) {
			update(r);
			return r;
		}
		if (r == -1) {
			update(l);
			return l;
		}
		if (t[l].p > t[r].p){
			t[l].r = merge(t[l].r, r);
			update(l);
			return l;
		}
		else{
			t[r].l = merge(l, t[r].l);
			update(r);
			return r;
		}
	}

	int it = 0;
	void insert(int &root, T v){
		int M = it++;
		t[M] = node(v);
		if (root == -1) {
			root = M;
			return;
		}
		root = merge(root, M);
	}

	T query(int &root, int L, int R){
		int l, m, r;
		split_implicit(root, R+1, m, r);
		split_implicit(m, L, l, m);

		T ans = t[m].min_s;
		l = merge(l, m);
		l = merge(l, r);
		root = l;
		return ans; 
	}
	void erase(int &root, int pos){
		int l, m, r;
		split_implicit(root, pos+1, m, r);
		split_implicit(m, pos, l, m);
		l = merge(l, r);
		root = l;
	}
};
