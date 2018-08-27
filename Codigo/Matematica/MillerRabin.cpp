// Teste de primalidade de Miller-Rabin
//
// Testa se n eh primo, n <= 3 * 10^18
//
// O(log(n)), considerando multiplicacao
// e exponenciacao constantes

// multiplicacao e exponenciacao rapidas
ll mul(ll x, ll y, ll m); // x*y mod m
ll pow(ll x, ll y, ll m); // x^y mod m

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;

	ll d = n - 1;
	int r = 0;
	while (d % 2 == 0) r++, d /= 2;

 	// com esses primos, o teste funciona garantido para n <= 3*10^18
	// funciona para n <= 3*10^24 com os primos ate 41
	int a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	// outra opcao para n <= 2^64:
	// int a[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

	for (int i = 0; i < 9; i++) {
		if (a[i] >= n) break;
		ll x = pow(a[i], d, n);
		if (x == 1 or x == n - 1) continue;

		bool deu = 1;
		for (int j = 0; j < r - 1; j++) {
			x = pow(x, 2, n);
			if (x == n - 1) deu = 0, break;
		}
		if (deu) return 0;
	}
	return 1;
}
