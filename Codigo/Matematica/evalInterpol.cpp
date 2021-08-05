// Avaliacao de Interpolacao
//
// Dado 'n' pontos (i, y[i]), i \in [0, n),
// avalia o polinomio de grau i-1 que passa
// por esses pontos em 'x'
// Tudo modular, precisa do mint
//
// O(n log n)

mint evaluate_interpolation(int x, vector<mint> y) {
	int n = y.size();

	vector<mint> sulf(n+1, 1), fat(n, 1);
	for (int i = n-1; i >= 0; i--) sulf[i] = sulf[i+1] * (x - i);
	for (int i = 1; i < n; i++) fat[i] = fat[i-1] * i;

	mint pref = 1, ans = 0;
	for (int i = 0; i < n; pref *= (x - i++)) {
		mint num = pref * sulf[i+1];

		mint den = fat[i] * fat[n-1 - i];
		if ((n-1 - i)%2) den *= -1;

		ans += y[i] * num / den;
	}
	return ans;
}
