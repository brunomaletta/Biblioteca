// Multipoint Evaluation And Interpolation
//
// Evaluation:
// 	Avalia o polinomio f(x) nos pontos p[0], p[1], ..., p[n-1]
// 
// Interpolation:
// 	Retorna o polinomio f(x) de grau n que
// 	satisfaz f(x) = y pra o conjunto de pontos x, y
//
// Precisa do ntt e
// - do divmod pro evaluate
// - da derivada pro interpolate
//
// O divmod e a derivada estao no arquivo powerSeries.cpp
//
// O(n log^2(n))

namespace multipoint {
	vector<poly> tree;
	void build(vector<mint>& p) {
		int n = p.size();
		tree.resize(2*n);
		for (int i = 0; i < n; i++) tree[n + i] = {-p[i], 1};
		for (int i = n - 1; i > 0; i--)
			tree[i] = convolution(tree[2*i], tree[2*i + 1]);
	}
	vector<mint> evaluate(poly& f, vector<mint>& p) {
		build(p);
		int n = p.size();
		vector<poly> ans(2 * n);
		ans[1] = divmod(f, tree[1]).second;
		for (int i = 2; i < 2 * n; i++)
			ans[i] = divmod(ans[i/2], tree[i]).second;
		vector<mint> results(n);
		for (int i = 0; i < n; i++) results[i] = ans[n + i][0];
		return results;
	}
	poly prod(vector<mint>& p, int l, int r) {
		if (l == r) return {-p[l], 1};
		int m = (l + r) / 2;
		return convolution(prod(p, l, m), prod(p, m + 1, r));
	}
	poly interpolate(vector<mint>& x, vector<mint>& y) {
		int n = x.size();
		poly p = D(prod(x, 0, n - 1));
		auto d = evaluate(p, x);
		vector<poly> ans(2 * n);
		for (int i = 0; i < n; i++) ans[n + i] = {y[i] / d[i]};
		for (int i = n - 1; i > 0; i--) {
			poly p1 = convolution(tree[2*i], ans[2*i + 1]);
			poly p2 = convolution(tree[2*i + 1], ans[2*i]);
			ans[i] = p1;
			for (int j = 0; j < p1.size(); j++) ans[i][j] += p2[j];
		}
		return ans[1];
	}
}
