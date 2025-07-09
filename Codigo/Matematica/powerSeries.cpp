// Operacoes em Polinomios e Series de Potencias
//
// Precisa do NTT
// O exp nao foi bem testado
//
// Fonte: github.com/celiopassos/competitive-programming/blob/master/algorithms/mathematics/formal_power_series.hpp
//
// D, I: O(n)
// inv, divmod, log e exp: O(n log(n))

using poly = vector<mint>;

const int MAGIC = 512;

poly D(poly p) {
	if (p.empty()) return p;
	for (int i = 0; i + 1 < p.size(); i++)
		p[i] = (i + 1) * p[i + 1];
	p.pop_back();
	return p;
}

poly I(poly p) {
	int n = p.size();
	p.push_back(0);
	for (int i = n - 1; i >= 0; i--)
		p[i + 1] = p[i] / (i + 1);
	p[0] = 0;
	return p;
}

poly inv(poly p) {
	poly q = {mint(1) / p[0]};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(2 * k);
		ntt(q, false);
		poly p0(2 * k);
		copy_n(p.begin(), min(k, n), p0.begin());
		ntt(p0, false);
		for (int i = 0; i < 2 * k; i++)
			q[i] *= 2 - p0[i] * q[i];
		ntt(q, true);
		q.resize(k);
	}
	q.resize(n);
	return q;
}

pair<poly, poly> divslow(const poly& a, const poly& b) {
	poly q, r = a;
	while (r.size() >= b.size()) {
		q.push_back(r.back() / b.back());
		if (q.back() != 0)
			for (int i = 0; i < b.size(); i++)
				r.end()[-i-1] -= q.back() * b.end()[-i-1];
		r.pop_back();
	}
	reverse(q.begin(), q.end());
	return {q, r};
}

// retorna (q, r) : a(x) = b(x) * q(x) + r(x)
pair<poly, poly> divmod(const poly& a, const poly& b) {
	if (a.size() < b.size()) return {{}, a};
	if (max(b.size(), a.size() - b.size()) < MAGIC) return divslow(a, b);
	poly ra = poly(a.rbegin(), a.rend());
	poly rb = poly(b.rbegin(), b.rend());
	int k = a.size() - b.size() + 1;
	rb.resize(k);
	poly irb = inv(move(rb)), q = convolution(ra, irb);
	q = poly(q.rend() - k, q.rend());
	poly r = convolution(move(q), b);
	for (int i = 0; i < r.size(); i++) r[i] = a[i] - r[i];
	while (r.size() > 1 && r.back() == 0) r.pop_back();
	return {q, r};
}

poly log(poly p) {
	assert(!p.empty() && p[0] == 1);
	int n = p.size();
	auto d = D(p), i = inv(p);
	auto r = convolution(d, i);
	r.resize(n - 1);
	return I(move(r));
}

poly exp(poly p) {
	assert(p.empty() || p[0] == 0);
	poly q = {1};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(k);
		poly b = log(q);
		for (int i = 0; i < k; i++) b[i] *= -1;
		b[0] += 1;
		for (int i = 0; i < min(n, k); i++) b[i] += p[i];
		q = convolution(q, b);
		q.resize(k);
	}
	q.resize(n);
	return q;
}
