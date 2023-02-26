// Fracao
//
// Funciona com o Big Int

template<typename T = int> struct frac {
	T num, den;
	template<class U, class V>
	frac(U num_ = 0, V den_ = 1) : num(num_), den(den_) {
		assert(den != 0);
		if (den < 0) num *= -1, den *= -1;
		T g = gcd(abs(num), den);
		num /= g, den /= g;
	}

	friend bool operator<(const frac& l, const frac& r) {
		return l.num * r.den < r.num * l.den;
	}
	friend frac operator+(const frac& l, const frac& r) {
		return {l.num*r.den + l.den*r.num, l.den*r.den};
	}
	friend frac operator-(const frac& l, const frac& r) {
		return {l.num*r.den - l.den*r.num, l.den*r.den};
	}
	friend frac operator*(const frac& l, const frac& r) {
		return {l.num*r.num, l.den*r.den};
	}
	friend frac operator/(const frac& l, const frac& r) {
		return {l.num*r.den, l.den*r.num};
	}
	friend ostream& operator<<(ostream& out, frac f) {
		out << f.num << '/' << f.den;
		return out;
	}
};
