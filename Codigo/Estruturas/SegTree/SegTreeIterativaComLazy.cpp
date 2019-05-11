// SegTree Iterativa com Lazy Propagation
//
// SegTree 1-based
// Valores iniciais devem estar em (seg[n], ... , seg[2*n-1])
// Query: soma do range [a, b], 0-based
// Update: soma x em cada elemento do range [a, b], 0-based
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

int seg[2*MAX];
int lazy[2*MAX];
int n;

void build() {
	for (int i = n - 1; i; i--) seg[i] = seg[2*i] + seg[2*i+1];
	memset(lazy, 0, sizeof(lazy));
}

// soma x na posicao p de tamanho tam
void poe(int p, int x, int tam) {
	seg[p] += x * tam;
	if (p < n) lazy[p] += x;
}

// atualiza todos os pais da folha p
void sobe(int p) {
	for (int tam = 2; p /= 2; tam *= 2)
		seg[p] = seg[2*p] + seg[2*p+1] + lazy[p] * tam;
}

// propaga o caminho da raiz ate a folha p
void prop(int p) {
	int tam = 1 << 29;
	for (int s = 30; s; s--, tam /= 2) {
		int i = p >> s;
		if (lazy[i]) {
			poe(2*i, lazy[i], tam);
			poe(2*i+1, lazy[i], tam);
			lazy[i] = 0;
		}
	}
}

int query(int a, int b) {
	prop(a += n), prop(b += n);
	int ret = 0;
	for(; a <= b; a /= 2, b /= 2) {
		if (a % 2 == 1) ret += seg[a++];
		if (b % 2 == 0) ret += seg[b--];
	}
	return ret;
}

void update(int a, int b, int x) {
	int a2 = a += n, b2 = b += n, tam = 1;
	for (; a <= b; a /= 2, b /= 2, tam *= 2) {
		if (a % 2 == 1) poe(a++, x, tam);
		if (b % 2 == 0) poe(b--, x, tam);
	}
	sobe(a2), sobe(b2);
}
