// Exponenciacao rapida
//
// (x^y mod m) em O(log(y))

typedef long long int ll;

ll pow(ll x, ll y, ll m) { // iterativo
	ll ret = 1;
	while (y){
		if (y & 1){
			ret *= x;
			ret %= m;
		}
		y >>= 1;
		x *= x;
		x %= m;
	}
	return ret;
}

ll pow(ll x, ll y, ll m) { // recursivo
	if (y == 0) return 1;

	ll ret = pow(x, y / 2, m);
	ret = (ret * ret) % m;
	if (y & 1) ret = (ret * x) % m;
	return ret;
}
