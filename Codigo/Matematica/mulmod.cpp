// Produto de dois long long mod m
//
// O(1)

typedef long long int ll;

ll mul(ll a, ll b, ll m) { // a*b % m
	ll ret = a*b - ll(a*(long double)b/m+0.5)*m;
	return ret < 0 ? ret+m : ret;
}
