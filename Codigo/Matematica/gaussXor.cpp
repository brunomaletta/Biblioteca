// Eliminacao Gaussiana de XOR
//
// insert(mask) insere uma mask no espaco vetorial
//
// O(log(MAXN))

int basis[LOG]; // basis[i] = mask do cara com bit mais significativo i
int rk; // tamanho da base

void insert(int mask) {
	for (int i = LOG - 1; i >= 0; i--) if (mask>>i&1) {
		if (!basis[i]) {
			basis[i] = mask, rk++;
			return;
		}
		mask ^= basis[i];
	}
}
