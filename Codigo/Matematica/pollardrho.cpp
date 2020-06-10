// Pollard's Rho Alg
//
// Usa o algoritmo de deteccao de ciclo de Brent
// A fatoracao nao sai necessariamente ordenada
// O algoritmo rho encontra um fator de n,
// e funciona muito bem quando n possui um fator pequeno
//
// Complexidades (considerando mul constante):
// rho - esperado O(n^(1/4)) no pior caso
// fact - esperado menos que O(n^(1/4) log(n)) no pior caso

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll(a*(long double)b/m+0.5)*m;
	return ret < 0 ? ret+m : ret;
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
 
	for (int i : {2, 325, 9375, 28178, 450775, 9780504, 795265022}) {
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
 
ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	if (n % 2 == 0) return 2;
 
	while (1) {
		ll x = 2, y = 2, ciclo = 2, i = 0, d = 1;
		ll c = uniform(1, n-1);
 
		while (d == 1) {
			if (++i == ciclo) ciclo *= 2, y = x;
			x = (mul(x, x, n) + c) % n;
 
			if (x == y) break;
 
			d = __gcd(abs(x-y), n);
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
