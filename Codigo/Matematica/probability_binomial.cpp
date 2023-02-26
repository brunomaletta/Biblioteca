// Binomial Distribution
//
// binom(n, k, p) retorna a probabilidade de k sucessos
// numa binomial(n, p)

double logfact[MAX];

void calc() {
	logfact[0] = 0;
	for (int i = 1; i < MAX; i++) logfact[i] = logfact[i-1] + log(i);
}

double binom(int n, int k, double p) {
	return exp(logfact[n] - logfact[k] - logfact[n-k] + k * log(p) + (n-k) * log(1 - p));
}
