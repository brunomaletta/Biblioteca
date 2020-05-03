// Aritmetica Modular
//
// O mod tem q ser primo

template<int p> struct mod_int{
	ll pow(ll b, ll e){
		if (e == 0) return 1;
		if (e == 1) return b;
		ll r = pow(b, e/2);
		r = (r*r)%p;
		if (e%2 == 1)
			r = (r*b)%p;
		return r;
	}
	ll inv(ll b){ return pow(b, p-2); }

	using m = mod_int;
	int v;
	mod_int(){}
	mod_int(ll v_):v(v_){
		if (v >= p || v <= -p)
			v %= p;
		if (v < 0) v += p;
	}
	m& operator+=(const m &a){
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator-=(const m &a){
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator*=(const m &a){
		v = (v*ll(a.v))%p;
		return *this;
	}
	m& operator/=(const m &a){
		v = (v*inv(a.v))%p;
		return *this;
	}
	m operator-(){ return m(-v); }
	m& operator^=(ll e){
		if (e < 0){
			v = inv(v);
			e = -e;
		}
		v = pow(v, e);
		return *this;
	}
	bool operator==(const m &a){ return v == a.v; }
	bool operator!=(const m &a){ return v != a.v; }
	friend ostream &operator<<(ostream &out, m a){
		return out << a.v;
	}
	friend m operator+(m a, m b){ return a+=b; }
	friend m operator-(m a, m b){ return a-=b; }
	friend m operator*(m a, m b){ return a*=b; }
	friend m operator/(m a, m b){ return a/=b; }
	friend m operator^(m a, ll e){ return a^=e; }

	static int fft_len(int n = -1){
		//max k such that 2^k | p-1
		if (p == 998244353)
			return 20;
		throw logic_error("find an order");
		return -1;
	}
	static m rt(bool f, int n, int N){
		//an element of order fft_len
		if (p == 998244353){
			m r(695449733);
			if (f) r = r^(-1);
			return r^(N/n);
		}

		throw logic_error("find a root");
		return -1;//return x so that x^(2^k) != x*x^(2^k) = 1
	}

};


typedef mod_int<1e9+7> mint;

vector<mint> fatt;

mint fat(int n) {
	if (n < fatt.size()) return fatt[n];
	if (!n) fatt.push_back(1);
	else fatt.push_back(n*fat(n-1));
	return fatt.back();
}
