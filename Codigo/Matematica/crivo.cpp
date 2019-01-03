// Variacoes do crivo de Eratosthenes

// "O" crivo
//
// Encontra maior divisor primo
// Um numero eh primo sse div[x] == x
// fact fatora um numero <= lim
// A fatoracao sai ordenada
//
// crivo - O(n log(log(n)))
// fact - O(log(n))

int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++) if (divi[i] == 1)
		for (int j = i; j <= lim; j += i) divi[j] = i;
}

void fact(vector<int>& v, int n) {
	if (n != divi[n]) fact(v, n/divi[n]);
	v.push_back(divi[n]);
}

// Crivo de divisores
//
// Encontra numero de divisores
// ou soma dos divisores
//
// O(n log(n))

int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++)
		for (int j = i; j <= lim; j += i) {
			// para numero de divisores
			divi[j]++;
			// para soma dos divisores
			divi[j] += i;
		}
}

// Crivo de totiente
//
// Encontra o valor da funcao
// totiente de Euler
//
// O(n log(log(n)))

int tot[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) tot[i] = i;

	for (int i = 2; i <= lim; i++) if (tot[i] == i)
		for (int j = i; j <= lim; j += i)
			tot[j] -= tot[j] / i;
}
