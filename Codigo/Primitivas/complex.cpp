// Complex
// 51773e

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

	//fft 
	static int fft_len(int N){
		int n = 1, log_n = 0;
		while (n <= N) { n <<= 1; log_n++; }
		return log_n;
	}
	static cplx rt(bool f, int n, int N){
		const static double PI = acos(-1);
		double alpha = (2*PI)/n;
		if (f) alpha = -alpha;
		return cplx(cos(alpha), sin(alpha));
	}
};

