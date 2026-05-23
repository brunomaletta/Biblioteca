// Chirp-Z Transform
// https://judge.yosupo.jp/submission/374113
//
// Precisa de NTT
//
// Avalia o polinomio p(x) nos pontos d, d * c, d * c^2, ... , d * c^(m-1)
//
// O(k log(k)) onde k = max(|p|,m)

poly chirpz(poly p, mint c, mint d, int m){
	assert(m >= 1);
	poly a = p; mint v = d;
	for (int i = 1; i < a.size(); ++i, v *= d) a[i] *= v;
	if (c.v == 0){ //pode ignorar esse if se a razao for sempre nao-nula
		mint a0 = (p.empty()) ? mint(0) : p[0];
		poly ret(m, a0);
		ret[0] = mint(0);
		for (auto x : a) ret[0] += x;
		return ret;
	}
	int n = p.size();
	mint ivc = c^(-1);
	auto upd = [&](poly &x, mint v){
		mint aux = v, mul = v;
		for (int i = 2; i < x.size(); ++i, aux *= v, mul *= aux) x[i] *= mul; 
	};
	upd(a, ivc); 
	reverse(a.begin(), a.end());
	poly b(m+n-1, 1); 
	upd(b, c);
	a = convolution(a,b);
	poly q(a.end() - (m+n-1), a.end());
	q.resize(m);
	upd(q, ivc);
	return q;
}



// Inverse Chirp-Z Transform
// https://judge.yosupo.jp/submission/374110
//
// Precisa de NTT e da derivada de serie formal (powerSeries.cpp)
//
// Encontra um polinomio p(x) de grau n-1 a partir de uma lista [y_0, ..., y_(n-1)]
// tal que p(d * c^i) = y_i para i = {0, ..., n-1} 
// (basicamente: faz interpolacao com uma progressao geometrica)
//
// Eh necessario que (d * c^i) != (d * c^j) (modulo MOD) para todo 0 <= i != j < n
//
// O(n log(n))

poly inv_chirpz(poly y, mint c, mint d){
	assert(c.v != 0 and d.v != 0);
	int n = y.size();
	auto aux = [&](auto &&self, int m)->poly{
		if (m == 1) return poly({-d, 1});
		int k = m/2;
		poly h = self(self, k);
		poly h2 = h;
		mint v = c^(-k), mul = v;
		for (int i = 1; i <= k; ++i, mul *= v) h2[i] *= mul;
		h = convolution(h, h2);
		v = c^(k*k);
		for (auto &x : h) x *= v;
		if ((m&1) == 0) return h;
		poly ret = h;
		ret.resize(m+1);
		v = - (d * (c^(m-1)));
		for (auto &x : ret) x *= v;
		for (int i = 1; i <= m; ++i) ret[i] += h[i-1];
		return ret;
	};

	poly g = aux(aux, n);
	poly q = chirpz(D(g), c, d, n);
	for (int i = 0; i < n; ++i) q[i] = y[i] / q[i];

	mint ivc = c^(-1), ivd = d^(-1), mul = ivd;
	poly f = chirpz(q, ivc, ivc, n);
	for (int i = 0; i < n; ++i, mul = mul * ivd) f[i] = -(f[i] * mul);

	poly ret = convolution(f,g);
	ret.resize(n);

	return ret;
}
