// Treap
//
// Usar static treap<int> t;
// Para usar, chamar o Rafael
//
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
		T sum;
		bool rev;
		node(){}
		node(T v):p(rng()), l(-1), r(-1), v(v), sz(1), rev(false){}
	} t[MAX];
	int it;
	//vector<node> t;
	treap(){ it = 0; }
	int size(int i){
		if (i == -1) return 0;
		return t[i].sz;
	}
	void fix(int i){
		if (i == -1) return;
		if (t[i].rev) {
			int &l = t[i].l;
			int &r = t[i].r;
			swap(l, r);
			t[i].sz = 1 + size(l) + size(r);
			if (l != -1)
				t[l].rev ^= true;
			if (r != -1)
				t[r].rev ^= true;
			t[i].rev = false;
		}
	}
	void update(int i){
		if (i == -1) return;
		t[i].sum = t[i].v;
		int l = t[i].l;
		int r = t[i].r;
		t[i].sz = 1 + size(l) + size(r);
	}

	void split_value(int i, int k, int &l, int &r){ //values must be ordered
		if (i == -1){
			l = -1; r = -1;
			return;
		}
		fix(i);
		if (t[i].v < k){
			split_value(t[i].r, k, l, r);
			t[i].r = l;
			l = i;
		}
		else{
			split_value(t[i].l, k, l, r);
			t[i].l = r;
			r = i;
		}
		update(i);
	}

	//implicit
	void split(int i, int k, int &l, int &r, int sz = 0){ //key
		if (i == -1){
			l = -1; r = -1;
			return;
		}
		fix(i);
		int inc = size(t[i].l); //quantidade elementos menor que k
		if (sz+inc < k){
			split(t[i].r, k, l, r, sz+inc+1);
			t[i].r = l;
			l = i;
		}
		else{
			split(t[i].l, k, l, r, sz);
			t[i].l = r;
			r = i;
		}
		update(i);
	}
	int merge(int l, int r){ //priority
		if (l == -1) return r;
		if (r == -1) return l;
		fix(l); fix(r);
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

	void insert(int &root, T v, int pos){
		int m = it++;
		t[m] = node(v);
		if (root == -1){
			root = m;
			return;
		}
		int l, r;
		split(root, pos, l, r);
		l = merge(l, m);
		l = merge(l, r);
		root = l;
	}

	T query(int &root, int M){
		int l, m, r;
		split(root, M+1, m, r);
		split(m, M, l, m);

		T ans = t[m].v;
		l = merge(l, m);
		l = merge(l, r);
		root = l;
		return ans; 
	}
	void reverse(int &root, int L, int R){
		int l, m, r;
		split(root, R+1, m, r);
		split(m, L, l, m);
		t[m].rev ^= 1;
		l = merge(l, m);
		l = merge(l, r);
		root = l;
	}
	void print(int i, int &size){
		if (i == -1) return;
		print(t[i].l, size);
		cout << "#" << size << ": " << t[i].v << endl;
		size++;
		print(t[i].r, size);
	}
};
