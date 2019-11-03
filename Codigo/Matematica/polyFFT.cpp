//FFT exemplos na main
//
//Soma O(n) & Multiplicacao O(nlogn)

const int MAX = 5e5;
const int MAX2 = (1 << 20);//(1 << (ceil(log2(MAX)) + 1)) + 1

const double PI = acos(-1);

struct cplx{
	double r, i;
	cplx(double r_ = 0, double i_ = 0):r(r_), i(i_){}
	const cplx operator+(const cplx &x) const{
		return cplx(r + x.r, i + x.i);
	}
	const cplx operator-(const cplx &x) const{
		return cplx(r - x.r, i - x.i);
	}
	const cplx operator*(double a) const {
		return cplx(r*a, i*a);
	}
	const cplx operator/(double a)const {
		return cplx(r/a, i/a);
	}
	const cplx operator*(const cplx x) const {
		return cplx(r*x.r - i*x.i, r*x.i + i*x.r);
	}
};

const cplx I(0, 1);
cplx X[MAX2], Y[MAX2];
int rev[MAX2];
cplx roots[MAX2];

cplx rt(int i, int n){
	double alpha = (2*i*PI)/n;
	return cplx(cos(alpha), sin(alpha));
}

void fft(cplx *a, bool f, int N){
	for (int i = 0; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	int l, r, m;
	for (int n = 2; n <= N; n *= 2){
		cplx root = (f ? rt(1, n) : rt(-1, n));
		roots[0] = 1;
		for (int i = 1; i < n/2; i++)
			roots[i] = roots[i-1]*root;
		for (int pos = 0; pos < N; pos += n){
			l = pos+0, r = pos+n/2, m = 0;
			while (m < n/2){
				auto t = roots[m]*a[r];
				a[r] = a[l] - t;
				a[l] = a[l] + t;
				l++; r++; m++;
			}
		}
	}
	if (f) for(int i = 0; i < N; i++) a[i] = a[i]/N;
}


//p(x) = at(i)*x^i
template<typename T> struct poly : vector<T> {
	poly(const vector<T> &coef):vector<T>(coef){}
	poly(unsigned size):vector<T>(size){}
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
		int n = 1, log_n = 0;
		while (n <= N) { n <<= 1; log_n++; }
		for (int i = 0; i < n; ++i){
			rev[i] = 0;
			for (int j = 0; j < log_n; ++j)
				if (i & (1<<j))
					rev[i] |= 1 << (log_n-1-j);
		}
		for (int i = 0; i < ln; i++) X[i] = l[i];
		for (int i = ln; i < n; i++) X[i] = 0;
		for (int i = 0; i < rn; i++) Y[i] = r[i];
		for (int i = rn; i < n; i++) Y[i] = 0;
		fft(X, false, n);//call dft if possible
		fft(Y, false, n);

		for (int i = 0; i < n; i++)
			Y[i] = X[i]*Y[i];

		fft(Y, true, n);
		poly<T> ans(N);
		for (int i = 0; i < N; i++){
			ans[i] = floor(Y[i].r + 0.25); //if T is integer
			//ans[i] = Y[i].r; //if T is floating point
		}
			

		while (!ans.empty() && ans.back() == 0)
			ans.pop_back();
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
	poly<int> mult = p*q;
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
