// FFT
//
// chamar com vector<cplx> para FFT, ou vector<mint> para NTT
//
// O(n log(n))
// 40a2bd

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

template<typename T> vector<T> convolution(vector<T> &a, vector<T> &b) {
	vector<T> l(a.begin(), a.end());
	vector<T> r(b.begin(), b.end());
	int ln = l.size(), rn = r.size();
	int N = ln+rn+1;
	int n = 1, log_n = 0;
	while (n <= N) { n <<= 1; log_n++; }
	vector<int> rev(n);
	for (int i = 0; i < n; ++i){
		rev[i] = 0;
		for (int j = 0; j < log_n; ++j)
			if (i & (1<<j))
				rev[i] |= 1 << (log_n-1-j);
	}
	assert(N <= n);
	l.resize(n);
	r.resize(n);
	fft(l, false, n, rev);
	fft(r, false, n, rev);
	for (int i = 0; i < n; i++)
		l[i] *= r[i];
	fft(l, true, n, rev);
	return l;
}
