// Crivo de Eratosthenes
//
// O(n log(log(n)))

int primo[MAX];
int n;

void crivo() {
	primo[1] = 0;
	for (int i = 2; i <= n; i++) primo[i] = 1;

	for (int i = 2; i*i <= n; i++) if (primo[i])
		for (int j = i*i; j <= n; j += i) primo[j] = 0;
}
