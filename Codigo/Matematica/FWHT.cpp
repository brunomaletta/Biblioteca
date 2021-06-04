// Fast Walsh Hadamard Transform
//
// FWHT<'|'>(f) eh SOS DP
// FWHT<'&'>(f) eh soma de superset DP
// Se chamar com ^, usar tamanho potencia de 2!!
//
// O(n log(n))

template<char op, bool inv = false, class T> vector<T> FWHT(vector<T> f) {
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
