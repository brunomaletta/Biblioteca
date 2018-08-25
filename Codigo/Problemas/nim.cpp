// Jogo de Nim
//
// Calcula movimento otimo do jogo classico de Nim
// Assume que o estado atual eh perdedor
// Funcao move retorna um par com a pilha (0 indexed)
// e quanto deve ser tirado dela
//
// MAX2 = teto do log do maior elemento
// possivel nas pilhas
//
// O(n)

int v[MAX], n;

pair<int, int> move() {
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
	return make_pair(p, v[p] - x);
}
