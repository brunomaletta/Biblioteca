// Miller-Rabin
//
// Testa se n eh primo, n <= 3 * 10^18
//
// O(log(n)), considerando multiplicacao
// e exponenciacao constantes

// multiplicacao modular

ll mul(ll a, ll b, ll m) {
	return (a*b-ll(a*(long double)b/m+0.5)*m+m)%m;
}

ll expo(ll a, ll b, ll m) {
	if (!b) return 1;
	ll ans = expo(mul(a, a, m), b/2, m);
	return b%2 ? mul(a, ans, m) : ans;
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;

	ll d = n - 1;
	int r = 0;
	while (d % 2 == 0) {
		r++;
		d /= 2;
	}

 	// com esses primos, o teste funciona garantido para n <= 2^64
	// funciona para n <= 3*10^24 com os primos ate 41
	for (int i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		if (i >= n) break;
		ll x = expo(i, d, n);
		if (x == 1 or x == n - 1) continue;

		bool deu = 1;
		for (int j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) {
				deu = 0;
				break;
			}
		}
		if (deu) return 0;
	}
	return 1;
}
