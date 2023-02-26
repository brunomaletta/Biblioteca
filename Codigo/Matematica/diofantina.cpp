// Equacao Diofantina Linear
//
// Encontra o numero de solucoes de a*x + b*y = c,
// em que x \in [lx, rx] e y \in [ly, ry]
// Usar o comentario para recuperar as solucoes
// (note que o b ao final eh b/gcd(a, b))
// Cuidado com overflow! Tem que caber o quadrado dos valores
//
// O(log(min(a, b)))

template<typename T> tuple<ll, T, T> ext_gcd(ll a, ll b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd<T>(b%a, a);
    return {g, y - b/a*x, x};
}

// numero de solucoes de a*[lx, rx] + b*[ly, ry] = c
template<typename T = ll> // usar __int128 se for ate 1e18
ll diophantine(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
	if (lx > rx or ly > ry) return 0;
	if (a == 0 and b == 0) return c ? 0 : (rx-lx+1)*(ry-ly+1);
	auto [g, x, y] = ext_gcd<T>(abs(a), abs(b));
	if (c % g != 0) return 0;
	if (a == 0) return (rx-lx+1)*(ly <= c/b and c/b <= ry);
	if (b == 0) return (ry-ly+1)*(lx <= c/a and c/a <= rx);
	x *= a/abs(a) * c/g, y *= b/abs(b) * c/g, a /= g, b /= g;

	auto shift = [&](T qt) { x += qt*b, y -= qt*a; };
	auto test = [&](T& k, ll mi, ll ma, ll coef, int t) {
		shift((mi - k)*t / coef);
		if (k < mi) shift(coef > 0 ? t : -t);
		if (k > ma) return pair<T, T>(rx+2, rx+1);
		T x1 = x;
		shift((ma - k)*t / coef);
		if (k > ma) shift(coef > 0 ? -t : t);
		return pair<T, T>(x1, x);
	};

	auto [l1, r1] = test(x, lx, rx, b, 1);
	auto [l2, r2] = test(y, ly, ry, a, -1);
	if (l2 > r2) swap(l2, r2);
	T l = max(l1, l2), r = min(r1, r2);
	if (l > r) return 0;
	ll k = (r-l) / abs(b) + 1;
	return k; // solucoes: x = l + [0, k)*|b|
}
