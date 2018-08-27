// Fatoracao pelo algoritmo Rho de Pollard
//
// Usa o algoritmo de deteccao de ciclo de Brent
// A fatoracao nao sai necessariamente ordenada
// O algoritmo rho encontra um fator de n,
// e funciona muito bem quando n possui um fator pequeno
// Eh recomendado chamar srand(time(NULL)) na main
//
// Complexidades:
// prime - O(log^2(n))
// rho - esperado O(n^(1/4) log(n)) no pior caso
// fact - esperado menos que O(n^(1/4) log^2(n)) no pior caso

ll mdc(ll a, ll b) {
	return !b ? a : mdc(b, a % b);
}

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

// teste de primalidade de
// Miller-Rabin
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
	// outra possibilidade para n <= 2^64:
	//int a[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
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

// acha um divisor de n
// tempo esperado no pior caso: O(n^(1/4) log(n))
// na pratica, eh bem mais rapido
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


// acha os divisores primos de n,
// nao necessariamente ordenados
void fact(ll n, vector<ll>& v) {
	if (n == 1) return;
	if (prime(n)) v.pb(n);
	else {
		ll d = rho(n);
		fact(d, v);
		fact(n / d, v);
	}
}
