// Teste de primalidade de Miller_rabin
//
// Testa se n eh primo, n <= 3 * 10^18
//
// O(log^3(n))

ll mul(ll x, ll y, ll m) {
	if (!y) return 0;

	ll ret = mul(x, y >> 1, m);
	ret = (ret + ret) % m;
	if (y & 1) ret = (ret + x) % m;
	return ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;

	ll ret = pow(x, y >> 1, m);
	ret = mul(ret, ret, m);
	if (y & 1) ret = mul(ret, x, m);
	return ret;
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

 	// com esses primos, o teste funciona garantido para n <= 3*10^18
	// funciona para n <= 3*10^24 com os primos ate 41
	int a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (int i = 0; i < 9; i++) {
		if (a[i] >= n) break;
		ll x = pow(a[i], d, n);
		if (x == 1 or x == n - 1) continue;

		bool deu = 1;
		for (int j = 0; j < r - 1; j++) {
			x = pow(x, 2, n);
			if (x == n - 1) {
				deu = 0;
				break;
			}
		}
		if (deu) return 0;
	}
	return 1;
}
