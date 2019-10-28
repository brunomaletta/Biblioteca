// Fatoracao pelo algoritmo Rho de Pollard
//
// Usa o algoritmo de deteccao de ciclo de Brent
// A fatoracao nao sai necessariamente ordenada
// O algoritmo rho encontra um fator de n,
// e funciona muito bem quando n possui um fator pequeno
// Eh recomendado chamar srand(time(NULL)) na main
//
// Complexidades (considerando mul constante):
// rho - esperado O(n^(1/4)) no pior caso
// fact - esperado menos que O(n^(1/4) log(n)) no pior caso

ll mdc(ll a, ll b) { return !b ? a : mdc(b, a % b); }

ll mul(ll a, ll b, ll m) {
	return (a*b-ll(a*(long double)b/m+0.5)*m+m)%m;	
}

ll exp(ll a, ll b, ll m) {
	if (!b) return 1;
	ll ans = exp(mul(a, a, m), b/2, m);
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

	int a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (int i = 0; i < 9; i++) {
		if (a[i] >= n) break;
		ll x = exp(a[i], d, n);
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

ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	if (n % 2 == 0) return 2;

	while (1) {
		ll x = 2, y = 2;
		ll ciclo = 2, i = 0;

		ll c = (rand() / (double) RAND_MAX) * (n - 1) + 1;
		ll d = 1;

		while (d == 1) {
			if (++i == ciclo) ciclo *= 2, y = x;
			x = (mul(x, x, n) + c) % n;

			if (x == y) break;

			d = mdc(abs(x - y), n);
		}

		if (x != y) return d;
	}
}

void fact(ll n, vector<ll>& v) {
	if (n == 1) return;
	if (prime(n)) v.pb(n);
	else {
		ll d = rho(n);
		fact(d, v);
		fact(n / d, v);
	}
}
