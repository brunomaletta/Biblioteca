// Karatsuba
//
// Os pragmas podem ajudar
// Para n ~ 2e5, roda em < 1 s
//
// O(n^1.58)

//#pragma GCC optimize("Ofast")
//#pragma GCC target ("avx,avx2")
template<typename T> void kar(T* a, T* b, int n, T* r, T* tmp) {
	if (n <= 64) {
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
			r[i+j] += a[i] * b[j];
		return;
	}
	int mid = n/2;
	T *atmp = tmp, *btmp = tmp+mid, *E = tmp+n;
	memset(E, 0, sizeof(E[0])*n);
	for (int i = 0; i < mid; i++) {
		atmp[i] = a[i] + a[i+mid];
		btmp[i] = b[i] + b[i+mid];
	}
	kar(atmp, btmp, mid, E, tmp+2*n);
	kar(a, b, mid, r, tmp+2*n);
	kar(a+mid, b+mid, mid, r+n, tmp+2*n);
	for (int i = 0; i < mid; i++) {
		T temp = r[i+mid];
		r[i+mid] += E[i] - r[i] - r[i+2*mid];
		r[i+2*mid] += E[i+mid] - temp - r[i+3*mid];
	}
}

template<typename T> vector<T> karatsuba(vector<T> a, vector<T> b) {
	int n = max(a.size(), b.size());
	while (n&(n-1)) n++;
	a.resize(n), b.resize(n);
	vector<T> ret(2*n), tmp(4*n);
	kar(&a[0], &b[0], n, &ret[0], &tmp[0]);
	return ret;
}
