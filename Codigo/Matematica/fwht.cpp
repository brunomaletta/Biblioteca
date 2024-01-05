// Fast Walsh Hadamard Transform
//
// FWHT<'|'>(f) eh SOS DP
// FWHT<'&'>(f) eh soma de superset DP
// Se chamar com ^, usar tamanho potencia de 2!!
//
// O(n log(n))

template<char op, class T> vector<T> FWHT(vector<T> f, bool inv = false) {
	int n = f.size();
	for (int k = 0; (n-1)>>k; k++) for (int i = 0; i < n; i++) if (i>>k&1) {
		int j = i^(1<<k);
		if (op == '^') f[j] += f[i], f[i] = f[j] - 2*f[i];
		if (op == '|') f[i] += (inv ? -1 : 1) * f[j];
		if (op == '&') f[j] += (inv ? -1 : 1) * f[i];
	}
	if (op == '^' and inv) for (auto& i : f) i /= n;
	return f;
}

// Generalizacao de FWHT de Xor
//
// Convolucao de soma mod B, usar tamanho potencia de B!!
// Precisa definir o tipo T e a raiz primitiva g
// satisfazendo g^b == g
//
// Se possivel, hardcodar a multiplicacao de matriz 
// feita em cada iteracao faz ficar bem mais rapido
//
// O(n b log_b(n))

template<class T>
vector<T> FWHT(vector<T> f, int b, T g, bool inv = false) {
	int n = f.size();
 
	vector<T> w(b);
	w[1] = g;
	for (int i = 2; i < b; i++) w[i] = w[i - 1] * g;
	w[0] = w[b - 1] * g;
 
	if (inv) reverse(w.begin() + 1, w.end());
 
	for (int pot = 1; pot < n; pot *= b) {
		for (int i = 0; i < n; i++) if (!(i / pot % b)) {
			vector<T> res(b);
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < b; k++)
					res[j] = res[j] + w[j * k % b] * f[i + k * pot];
				if (inv) res[j] = res[j] / b;
			}
			for (int j = 0; j < b; j++) f[i + j * pot] = res[j];
		}
	}
 
	return f;
}

// Exemplos da FWHT Generalizada:
//
// mod 7, resposta mod 998244353:
// T = mint, g = 14553391
//
// mod 3, resposta cabe em um long long:
// T = array<ll, 2>, g = {0, 1};
//
// using T = array<ll, 2>;
// T operator +(const T& a, const T& b) {
// 	return T{a[0] + b[0], a[1] + b[1]};
// }
// T operator *(const T& a, const T& b) {
// 	return T{a[0] * b[0] - a[1] * b[1], 
// 		     a[0] * b[1] + a[1] * b[0] - a[1] * b[1]};
// };
// T operator /(const T& a, const int& b) {
// 	return T{a[0] / b, a[1] / b};
// }
