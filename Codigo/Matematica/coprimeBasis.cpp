// Coprime Basis
//
// Dado um conjunto de elementos A constroi uma base B
// de fatores coprimos tal que todo elemento A[i] 
// pode ser escrito como A[i] = \prod B[j]^p_j
//
// Pior caso: O(n^2*log(MAX) + n*log^3(MAX))
// Esperado: O(n^2*log(MAX) + n*log(MAX)*loglog^2(MAX))
// b853c8

template <typename T> struct coprime_basis {
	vector<T> basis;
	coprime_basis() {}
	coprime_basis(vector<T> v) {
		for (T i : v) insert(i);
	}

	void reduce_pair(T &x, T &y) {
		bool swp = false;
		if (x < y) swap(x, y), swp ^= 1;
		while (y > 1 and x % y == 0) {
			x /= y;
			if (x < y) swap(x, y), swp ^= 1;
		}
		if (swp) swap(x, y);
	}

	void solve_inner(T &x, T &y) {
		vector<T> curr = {x, y};
		for (int it = 1; it < curr.size(); it++) {
			for (int i = 0; i < it; i++) {
				reduce_pair(curr[i], curr[it]);
				if (curr[it] == 1) break;
				if (curr[i] == 1) continue;
				T g = gcd(curr[i], curr[it]);
				if (g > 1) {
					curr[it] /= g, curr[i] /= g;
					curr.push_back(g);
				}
			}
		}
		x = curr[0], y = curr[1];
		for (int i = 2; i < curr.size(); i++) if (curr[i] > 1)
			basis.push_back(curr[i]);
	}

	void insert(T x) {
		vector<int> rem;
		for (int i = 0; i < basis.size(); i++) {
			T &y = basis[i];
			reduce_pair(x, y);
			if (x == 1) break;
			if (gcd(x, y) > 1) solve_inner(x, y);
		}
		for (int i = int(basis.size())-1; i >= 0; i--) if (basis[i] == 1) {
			swap(basis[i], basis.back());
			basis.pop_back();
		}
		if (x > 1) basis.push_back(x);
	}

	vector<int> factor(T x) {
		vector<int> fat(basis.size());
		for (int i = 0; i < basis.size(); i++) {
			while (x % basis[i] == 0) x /= basis[i], fat[i]++;
		}
		return fat;
	}
};
