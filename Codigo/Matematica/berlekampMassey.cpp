// Berlekamp-Massey
//
// guess_kth(s, k) chuta o k-esimo (0-based) termo
// de uma recorrencia linear que gera s
// Para uma rec. lin. de ordem x, se passar 2x termos
// vai gerar a certa
// Usar aritmetica modular
//
// Pro fast_evaluate, precisa de ntt e divmod (powerSeries.cpp)
//
// Complexidades: (n = |s|)
// evaluate: O(n^2 log k)
// fast_evaluate: O(n log n log k)
// berlekampMassey: O(n^2 + O(evaluate))

template<typename T> T evaluate(vector<T> c, vector<T> s, ll k) {
	int n = c.size();
	assert(c.size() <= s.size());

	auto mul = [&](const vector<T> &a, const vector<T> &b) {
		vector<T> ret(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++)
			ret[i+j] += a[i] * b[j];
		for (int i = ret.size()-1; i >= n; i--) for (int j = n-1; j >= 0; j--)
			ret[i-j-1] += ret[i] * c[j];
		ret.resize(min<int>(ret.size(), n));
		return ret;
	};

	vector<T> a = n == 1 ? vector<T>({c[0]}) : vector<T>({0, 1}), x = {1};
	while (k) {
		if (k&1) x = mul(x, a);
		a = mul(a, a), k >>= 1;
	}
	x.resize(n);

	T ret = 0;
	for (int i = 0; i < n; i++) ret += x[i] * s[i];
	return ret;
}

mint fast_evaluate(poly c, poly s, ll k) {
	if (k < s.size()) return s[k];
	int n = c.size();

	poly f(n + 1, 1);
	for (int i = 0; i < n; i++) f[i] = -c[n-i-1];

	poly a = {0, 1}, x = {1};
	while (k) {
		if (k&1) x = divmod(convolution(x, a), f).second;
		a = divmod(convolution(a, a), f).second, k >>= 1;
	}

	mint ret = 0;
	for (int i = 0; i < x.size(); i++) ret += x[i] * s[i];
	return ret;
}

template<typename T> vector<T> berlekamp_massey(vector<T> s) {
	int n = s.size(), l = 0, m = 1;
	vector<T> b(n), c(n);
	T ld = b[0] = c[0] = 1;
	for (int i = 0; i < n; i++, m++) {
		T d = s[i];
		for (int j = 1; j <= l; j++) d += c[j] * s[i-j];
		if (d == 0) continue;
		vector<T> temp = c;
		T coef = d / ld;
		for (int j = m; j < n; j++) c[j] -= coef * b[j-m];
		if (2 * l <= i) l = i + 1 - l, b = temp, ld = d, m = 0;
	}
	c.resize(l + 1);
	c.erase(c.begin());
	for (T& x : c) x = -x;
	return c;
}

template<typename T> T guess_kth(const vector<T>& s, ll k) {
	auto c = berlekamp_massey(s);
	return evaluate(c, s, k);
}
