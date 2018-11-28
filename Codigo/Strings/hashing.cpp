// String hashing
//
// String deve ter valores [1, x]
// p deve ser o menor primo maior que x
// Para evitar colisao: testar mais de um
// mod; só comparar strings do mesmo tamanho
//
// Complexidades:
// build - O(|s|)
// get_hash - O(1)

typedef long long ll;

ll h[MAX], power[MAX];
const int p = 31, m = 1e9+7;
int n; char s[MAX];

void build() {
	power[0] = 1;
	for (int i = 1; i < n; i++) power[i] = power[i-1]*p % m;
	h[0] = s[0];
	for (int i = 1; i < n; i++) h[i] = (h[i-1]*p + s[i]) % m;
}

ll get_hash(int i, int j) {
	if (!i) return h[j];
	return (h[j] - h[i-1]*power[j-i+1] % m + m) % m;
}
