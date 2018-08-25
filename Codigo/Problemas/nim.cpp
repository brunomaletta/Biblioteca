// Jogo de Nim
//
// calcula movimento otimo
// do jogo classico de Nim
// assume que o estado atual
// eh perdedor
//
// MAX2 = teto do log do maior elemento
// possivel nas pilhas
//
// O(n)

int v[MAX], n;

ii move() {
	int x = 0;
	for (int j = 0; j < n; j++) x ^= v[j];

	int p = -1;
	for (int i = 1 << MAX2; i; i >>= 1) if (x & i) {
		for (int j = 0; j < n; j++) if (v[j] & i) {
			p = j;
			break;
		}
		break;
	}

	x ^= v[p];
	return mp(p, v[p] - x);
}
