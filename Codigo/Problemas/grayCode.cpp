// Gray Code
//
// Gera uma permutacao de 0 a 2^n-1, de forma que
// duas posicoes adjacentes diferem em exatamente 1 bit
//
// O(2^n)

vector<int> gray_code(int n) {
	vector<int> ret(1<<n);
	for (int i = 0; i < (1<<n); i++) ret[i] = i^(i>>1);
	return ret;
}
