// Ordem de elemento do grupo
//
// Calcula a ordem de a em Z_n
// O grupo Zn eh ciclico sse n = 
// 1, 2, 4, p^k ou 2 p^k, p primo impar
// Retorna -1 se nao achar
//
// O(sqrt(n) log(n))

int tot(int n); // totiente em O(sqrt(n))
int expo(int a, int b, int m); // (a^b)%m em O(log(b))

// acha todos os divisores ordenados em O(sqrt(n))
vector<int> div(int n) {
	vector<int> ret1, ret2;
	for (int i = 1; i*i <= n; i++) if (n % i == 0) {
		ret1.push_back(i);
		if (i*i != n) ret2.push_back(n/i);
	}

	for (int i = ret2.size()-1; i+1; i--) ret1.push_back(ret2[i]);
	return ret1;
}

int ordem(int a, int n) {
	vector<int> v = div(tot(n));
	for (int i : v) if (expo(a, i, n) == 1) return i;
	return -1;
}
