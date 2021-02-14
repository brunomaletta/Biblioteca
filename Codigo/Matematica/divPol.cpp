// Divisao de Polinomios
//
// Divide p1 por p2
// Retorna um par com o quociente e o resto
// Os coeficientes devem estar em ordem
// decrescente pelo grau. Ex:
// 3x^2 + 2x - 1 -> [3, 2, -1]
//
// O(nm), onde n e m sao os tamanhos dos
// polinomios

typedef vector<int> vi;

pair<vi, vi> div(vi p1, vi p2) {
	vi quoc, resto;
	int a = p1.size(), b = p2.size();
	for (int i = 0; i <= a - b; i++) {
		int k = p1[i] / p2[0];
		quoc.pb(k);
		for (int j = i; j < i + b; j++)
			p1[j] -= k * p2[j - i];
	}

	for (int i = a - b + 1; i < a; i++)
		resto.pb(p1[i]);

	return mp(quoc, resto);
}
