// Algoritmo de Euclides
//
// O(log(min(a, b)))

int mdc(int a, int b) {
	return !b ? a : mdc(b, a % b);
}
