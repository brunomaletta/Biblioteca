// Algoritmo de Euclides
//
// O(log(min(a, b)))
// 7dbc22

int mdc(int a, int b) {
	return !b ? a : mdc(b, a % b);
}
