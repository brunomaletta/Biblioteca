// Fatoracao pelo algoritmo Rho de Pollard
//
// Usa o algoritmo de deteccao de ciclo de Brent
// A fatoracao nao sai necessariamente ordenada
// O algoritmo rho encontra um fator de n,
// e funciona muito bem quando n possui um fator pequeno
// Eh recomendado chamar srand(time(NULL)) na main
// A funcao pow deve chamar mul, para nao dar overflow
//
// Complexidades (considerando mul e pow constantes):
// rho - esperado O(n^(1/4)) no pior caso
// fact - esperado menos que O(n^(1/4) log(n)) no pior caso

ll mdc(ll a, ll b);
ll mul(ll a, ll b, ll m);
ll pow(ll a, ll b, ll m);
bool prime(ll n); // Miller-Rabin O(log^2(n))

ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	if (n % 2 == 0) return 2;

	while (1) {
		ll x = 2, y = 2;
		ll ciclo = 2, i = 0;

		// tenta com essa constante
		ll c = (rand() / (double) RAND_MAX) * (n - 1) + 1;
		// divisor
		ll d = 1;

		while (d == 1) {
			// algoritmo de Brent
			if (++i == ciclo) ciclo *= 2, y = x;
			x = (pow(x, 2, n) + c) % n;

			// x = y -> ciclo
			// tenta com outra constante
			if (x == y) break;

			d = mdc(abs(x - y), n);
		}

		// sucesso -> retorna o divisor
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
