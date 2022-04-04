// Complex
// a23731

struct cplx{
	double r, i;
	cplx(complex<double> c):r(c.real()), i(c.imag()){}
	cplx() : r(0), i(0){}
	cplx(double r_, double i_ = 0):r(r_), i(i_){}
	double abs(){ return hypot(r, i); }
	double abs2(){ return r*r + i*i; }
	cplx inv() { return cplx(r/abs2(), i/abs2()); }
	cplx& operator+=(cplx a){
		r += a.r; i += a.i;
		return *this;
	}
	cplx& operator-=(cplx a){
		r -= a.r; i -= a.i;
		return *this;
	}
	cplx& operator*=(cplx a){
		double r_ = r*a.r - i*a.i;
		double i_ = r*a.i + i*a.r;
		r = r_;
		i = i_;
		return *this;
	}
	cplx conj(){
		return cplx(r, -i);
	}
	cplx& operator/=(cplx a){
		auto a_ = a.inv();
		return (*this)*=a_;
	}
	cplx operator-(){ return cplx(-r, -i); }
	cplx& operator^=(double e){
		return *this = pow(complex<double>(r, i), e);
	}
	friend ostream &operator<<(ostream &out, cplx a){
		return out << a.r << " + " << a.i << "i";
	}
	friend cplx operator+(cplx a, cplx b){ return a+=b; }
	friend cplx operator-(cplx a, cplx b){ return a-=b; }
	friend cplx operator*(cplx a, cplx b){ return a*=b; }
	friend cplx operator/(cplx a, cplx b){ return a/=b; }
	friend cplx operator^(cplx a, double e){ return a^=e; }

	static void fill_rt(bool f, int n, int N, vector<cplx> &roots) {
		const static double PI = acosl(-1);
		for (int i = 0; i < n/2; i++){
			double alpha = i*((2*PI)/n);
			if (f) alpha = -alpha;
			roots[i] = cplx(cos(alpha), sin(alpha));
		}
	}
};

