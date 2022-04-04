// Aritmetica Modular
//
// O mod tem q ser primo
// a6879d

template<int p> struct mod_int {
	ll pow(ll b, ll e) {
		if (e == 0) return 1;
		ll r = pow(b*b%p, e/2);
		if (e%2 == 1) r = (r*b)%p;
		return r;
	}
	ll inv(ll b) { return pow(b, p-2); }

	using m = mod_int;
	int v;
	mod_int() : v(0) {}
	mod_int(ll v_) {
		v = v_;
		if (v >= p or v <= -p) v %= p;
		if (v < 0) v += p;
	}
	m& operator+=(const m &a) {
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator-=(const m &a) {
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator*=(const m &a) {
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator/=(const m &a) {
		v = v* inv(a.v) % p;
		return *this;
	}
	m operator-(){ return m(-v); }
	m& operator^=(ll e) {
		if (e < 0){
			v = inv(v);
			e = -e;
		}
		v = pow(v, e%(p-1));
		return *this;
	}
	bool operator==(const m &a) { return v == a.v; }
	bool operator!=(const m &a) { return v != a.v; }

	friend istream &operator>>(istream &in, m& a) {
		ll val; in >> val;
		a = m(val);
		return in;
	}
	friend ostream &operator<<(ostream &out, m a) {
		return out << a.v;
	}
	friend m operator+(m a, m b) { return a+=b; }
	friend m operator-(m a, m b) { return a-=b; }
	friend m operator*(m a, m b) { return a*=b; }
	friend m operator/(m a, m b) { return a/=b; }
	friend m operator^(m a, ll e) { return a^=e; }

	static void fill_rt(bool f, int n, int N, vector<m> &roots) {
		m r;
		int ord;
		if (p == 998244353) {
			r = 102292;
			ord = (1 << 23);
		}
		else if (p == 754974721) {
			r = 739831874;
			ord = (1 << 24);
		}
		else throw logic_error("invalid prime");

		while (ord != N){
			r = r*r;
			ord /= 2;
		}
		if (f) r = r^(-1);
		roots[0] = 1;
		r = r^(N/n);
		for (int i = 1; i < n/2; i++) roots[i] = roots[i-1]*r;
	}
};

typedef mod_int<(int)1e9+7> mint;

