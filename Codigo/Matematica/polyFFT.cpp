// FFT
//
// Exemplos na main
//
// Soma O(n) & Multiplicacao O(nlogn)

template<typename T> struct poly : vector<T> {
	poly(const vector<T> &coef):vector<T>(coef){}
	poly(unsigned size, T val = 0):vector<T>(size, val){}
	poly(){}
	T operator()(T x){
		T ans = 0, curr_x(1);
		for (auto c : *this) {
			ans = ans+c*curr_x;
			curr_x = curr_x*x;
	
		}
		return ans;
	}
	poly<T> operator+(const poly<T> &r){
		const poly<T> &l = *this;
		int sz = max(l.size(), r.size());
		poly<T> ans(sz);
		for (unsigned i = 0; i < l.size(); i++)
			ans[i] = ans[i]+l[i];
		for (unsigned i = 0; i < r.size(); i++)
			ans[i] = ans[i]+r[i];
		return ans;
	}
	poly<T> operator-(poly<T> &r){
		for (auto &it : r) it = -it;
		return (*this)+r;
	}
	void fix(int k){
		if (k < this->size()) throw logic_error("normalizando errado");
		while (this->size() < k) this->push_back(0);
	}
	pair<poly<T>, poly<T>> split(){
		const poly<T> &p = *this;
		poly<T> l, r;
		for (int i = 0; i < p.size(); i++)
			if (i&1) l.push_back(p[i]);
			else r.push_back(p[i]);
		return {l, r};
	}
	poly<T> operator*(const poly<T> r){
		const poly<T> &l = *this;
		int ln = l.size(), rn = r.size();
		int N = ln+rn+1;
		int log_n = T::fft_len(N);
		int n = 1 << log_n;
		vector<int> rev(n);

		for (int i = 0; i < n; ++i){
			rev[i] = 0;
			for (int j = 0; j < log_n; ++j)
				if (i & (1<<j))
					rev[i] |= 1 << (log_n-1-j);
		}
		if (N > n) throw logic_error("resulting poly to big");
		vector<T> X(n), Y(n);

		for (int i = 0; i < ln; i++) X[i] = l[i];
		for (int i = ln; i < n; i++) X[i] = 0;
		for (int i = 0; i < rn; i++) Y[i] = r[i];
		for (int i = rn; i < n; i++) Y[i] = 0;

		fft(X, false, log_n, n, rev);
		fft(Y, false, log_n, n, rev);

		for (int i = 0; i < n; i++)
			Y[i] = X[i]*Y[i];

		fft(Y, true, log_n, n, rev);
		poly<T> ans(N);
		for (int i = 0; i < N; i++)
			ans[i] = Y[i];
		
		//	while (!ans.empty() && ans.back() == 0)
		//		ans.pop_back();
		return ans;
	}
	pair<poly<T>, T> briot_ruffini(T r){//for p = Q(x - r) + R, returns (Q, R)
		const poly<T> &l = *this;
		int sz = l.size();
		if (sz == 0) return {poly<T>(0), 0};
		poly<T> q(sz - 1);
		q.back() = l.back();
		for (int i = q.size()-2; i >= 0; i--){
			cout << i << "~" << q.size() << endl;
			q[i] = q[i+1]*r + l[i+1];
		}
		return {q, q[0]*r + l[0]};
	}
};


template<typename T> ostream& operator<<(ostream &out, const poly<T> &p){
	if (p.empty()) return out;
	out << p.at(0);
	for (int i = 1; i < p.size(); i++)
		out << " + " << p.at(i) << "x^" << i;
	out << endl;
	return out;
}

int main(){ _
	poly<int> p({-2, -1, 2, 1});
	poly<int> q({1, 1, 1});
	poly<int> sum = p+q;
	poly<int> mult = p*q;//int doesnt support mult, type should be cplx or mod_int<P> 
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
	cout << "pq: " << mult << endl;
	for (int i = 1; i <= 50; i++){
		auto P = p(i), Q = q(i), M = mult(i);
		cout << P*Q << "\t\tvs\t\t" << M << endl;
		if (abs(P*Q - M) > 1e-5) throw logic_error("bad implementation :(");
	}
	cout << "sucesso!" << endl;
	exit(0);
	for (int root : {1, -1, 2, -2, 3}){
		poly<int> t; int r;
		tie(t, r) = p.briot_ruffini(root);
		cout << p << "/" << poly<int>({-root, 1});
		cout << " = " << endl;
		cout << t << " + " << r << endl;
		cout << endl;
	}

	exit(0);
}
