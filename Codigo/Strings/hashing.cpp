// String hashing
//
// String deve ter valores [1, x]
// p deve ser o menor primo maior que x
// Para evitar colisao: testar mais de um
// mod; so comparar strings do mesmo tamanho
// ex : str_hash<31, 1e9+7> h(s);
//      ll val = h(10, 20);
//
// Complexidades:
// build - O(|s|)
// get_hash - O(1)

typedef long long ll;

template<int P, int MOD> struct str_hash {
	int n;
	string s;
	vector<ll> h, power;
	str_hash(string s_): n(s_.size()), s(s_), h(n), power(n){
		power[0] = 1;
		for (int i = 1; i < n; i++) power[i] = power[i-1]*P % MOD;
		h[0] = s[0];
		for (int i = 1; i < n; i++) h[i] = (h[i-1]*P + s[i]) % MOD;
	}
	ll operator()(int i, int j){
		if (!i) return h[j];
		return (h[j] - h[i-1]*power[j-i+1] % MOD + MOD) % MOD;
	}
};
