// Algoritmo de Euclides
//
// O(log(min(a, b)))
// Na pratica, pode ser considerado O(1)

int mdc(int a, int b) {
	return !b ? a : mdc(b, a % b);
}
