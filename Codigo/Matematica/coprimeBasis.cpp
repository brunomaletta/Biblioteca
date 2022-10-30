// Coprime Basis
//
// Dado um conjunto de elementos A constroi uma base B
// de fatores coprimos tal que todo elemento A[i] 
// pode ser fatorado como A[i] = \prod B[j]^p_ij
//
// Sendo n o número de inserts, a complexidade esperada fica
// O(n*(n*loglog(MAX) + log(MAX)^2))
// 
// No pior caso, podemos trocar n*loglog(MAX) por
// se MAX <= 1e6 fica 8*n
// se MAX <= 1e9 fica 10*n
// se MAX <= 1e18 fica 16*n
// se MAX <= 1e36 fica 26*n
//
// 70de13

template <typename T> struct coprime_basis {
	vector<T> basis;
	
	coprime_basis() {}
	coprime_basis(vector<T> v) {
		for (T i : v) insert(i);
	}
	
	void insert(T z) {
		int n = basis.size();
		basis.push_back(z);
		for (int i = n; i < basis.size(); i++) {
			for (int j = (i != n) ? i+1 : 0; j < int(basis.size()); j++) {
				if (i == j) continue;
				T &x = basis[i];
				if (x == 1) {
					j = INF;
					continue;
				}
				T &y = basis[j];
				T g = gcd(x, y);
				if (g == 1) continue;
				y /= g;
				x /= g;
				basis.push_back(g);
			}
		}
		int j = 0;
		for (int i = 0; i < basis.size(); i++) {
			if (basis[i] == 1) continue;
			basis[j++] = basis[i];
		}
		while (basis.size() != j) basis.pop_back();
	}

	vector<int> factor(T x) {
		vector<int> fat(basis.size());
		for (int i = 0; i < basis.size(); i++) {
			while (x % basis[i] == 0) x /= basis[i], fat[i]++;
		}
		return fat;
	}
};
