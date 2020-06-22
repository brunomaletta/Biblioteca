// FFT
//
// Exemplos na main
//
// Soma O(n) & Multiplicacao O(nlogn)

template<typename T> void fft(vector<T> &a, bool f, int N, vector<int> &rev){
	for (int i = 0; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	int l, r, m;
	vector<T> roots(N);
	for (int n = 2; n <= N; n *= 2){
		T root = T::rt(f, n, N);
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
	if (f) {
		auto invN = T(1)/N;
		for(int i = 0; i < N; i++) a[i] = a[i]*invN;
	}
}


template<typename T> struct poly : vector<T> {
	poly(const vector<int> &coef):vector<T>(coef.size()){
		for (int i = 0; i < coef.size(); i++) this->at(i) = coef[i];
	}
	poly(const vector<T> &coef):vector<T>(coef){}
	poly(unsigned size, T val = 0):vector<T>(size, val){}
	poly(){}
	T operator()(T x){
		T ans = 0, curr_x(1);
		for (auto c : *this) {
			ans += c*curr_x;
			curr_x *= x;
		}
		return ans;
	}
	poly<T> operator+(const poly<T> &r){
		poly<T> l = *this;
		int sz = max(l.size(), r.size());
		l.resize(sz);
		for (int i = 0; i < r.size(); i++)
			l[i] += r[i];
		return l;
	}
	poly<T> operator-(poly<T> &r){
		for (auto &it : r) it = -it;
		return (*this)+r;
	}
	poly<T> operator*(poly<T> r){
		poly<T> l = *this;
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
		l.resize(n);
		r.resize(n);
		fft(l, false, n, rev);
		fft(r, false, n, rev);
		for (int i = 0; i < n; i++)
			l[i] *= r[i];
		fft(l, true, n, rev);
		return l;
	}
	friend ostream& operator<<(ostream &out, const poly<T> &p){
		if (p.empty()) return out;
		out << p.at(0);
		for (int i = 1; i < p.size(); i++)
			out << " + " << p.at(i) << "x^" << i;
		out << endl;
		return out;
	}
};

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;

using mint = mod_int<MOD>;

int main(){
	uniform_int_distribution<int> uid(0, MOD-1);
	int n = (1 << mint::fft_len()/2);
	auto rand_vec = [&](){
		vector<int> rd(n);
		for (int &i : rd) i = uid(rng);
		return rd;
	};

	poly<mint> p = rand_vec();
	poly<mint> q = rand_vec();
	poly<mint> sum = p+q;
	poly<mint> mult = p*q; 
	for (int i = 1; i <= 5000; i++){
		int x = uid(rng);
		auto P = p(x), Q = q(x), M = mult(x);
		if (P*Q != M) throw logic_error("bad implementation :(");
	}
	cout << "sucesso!" << endl;
	exit(0);

	exit(0);
}
