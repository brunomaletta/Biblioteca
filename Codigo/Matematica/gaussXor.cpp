// Eliminacao Gaussiana de XOR
//
// insert(mask) insere uma mask no espaco vetorial
// get(X) retorna outra uma mask com os caras da base
// cujo xor da X, ou -1 se n tem como
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

int get(int mask) {
	int ret = 0;
	for (int i = LOG - 1; i >= 0; i--) if (mask>>i&1) {
		if (!basis[i]) return -1;
		mask ^= basis[i], ret |= (1<<i);
	}
	return ret;
}
