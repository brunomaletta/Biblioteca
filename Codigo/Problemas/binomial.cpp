// Binomial modular
//
// Computa C(n, k) mod m em O(m + log(m) log(n))
// = O(rapido)

ll divi[MAX];

ll expo(ll a, ll b, ll m) {
	if (!b) return 1;
	ll ans = expo(a*a%m, b/2, m);
	if (b%2) ans *= a;
	return ans%m;
}

ll inv(ll a, ll b){
	return 1<a ? b - inv(b%a,a)*b/a : 1;
}

template<typename T> tuple<T, T, T> ext_gcd(T a, T b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b%a, a);
    return {g, y - b/a*x, x};
}

template<typename T = ll> struct crt {
	T a, m;

	crt() : a(0), m(1) {}
	crt(T a_, T m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		auto [g, x, y] = ext_gcd(m, C.m);
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		T lcm = m/g*C.m;
		T ans = a + (x*(C.a-a)/g % (C.m/g))*m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
};

pair<ll, ll> divide_show(ll n, int p, int k, int pak) {
	if (n == 0) return {0, 1};
	ll blocos = n/pak, falta = n%pak;
	ll periodo = divi[pak], resto = divi[falta];
	ll r = expo(periodo, blocos, pak)*resto%pak;

	auto rec = divide_show(n/p, p, k, pak);
	ll y = n/p + rec.first;
	r = r*rec.second % pak;

	return {y, r};
}

ll solve_pak(ll n, ll x, int p, int k, int pak) {
	divi[0] = 1;
	for (int i = 1; i <= pak; i++) {
		divi[i] = divi[i-1];
		if (i%p) divi[i] = divi[i] * i % pak;
	}

	auto dn = divide_show(n, p, k, pak), dx = divide_show(x, p, k, pak),
		 dnx = divide_show(n-x, p, k, pak);
	ll y = dn.first-dx.first-dnx.first, r =
		(dn.second*inv(dx.second, pak)%pak)*inv(dnx.second, pak)%pak;
	return expo(p, y, pak) * r % pak;
}

ll solve(ll n, ll x, int mod) {
	vector<pair<int, int>> f;
	int mod2 = mod;
	for (int i = 2; i*i <= mod2; i++) if (mod2%i==0) {
		int c = 0;
		while (mod2%i==0) mod2 /= i, c++;
		f.push_back({i, c});
	}
	if (mod2 > 1) f.push_back({mod2, 1});
	crt ans(0, 1);
	for (int i = 0; i < f.size(); i++) {
		int pak = 1;
		for (int j = 0; j < f[i].second; j++) pak *= f[i].first;
		ans = ans * crt(solve_pak(n, x, f[i].first, f[i].second, pak), pak);
	}
	return ans.a;
}
