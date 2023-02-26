// Produto de dois long long mod m
//
// O(1)

ll mul(ll a, ll b, ll m) { // a*b % m
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}
