// Simplex
//
// Maximiza c^T x s.t. Ax <= b, x >= 0
//
// O(2^n), porem executa em O(n^3) no caso medio

const double eps = 1e-7;

namespace Simplex {
	vector<vector<double>> T;
	int n, m;
	vector<int> X, Y;

	void pivot(int x, int y) {
		swap(X[y], Y[x-1]);
		for (int i = 0; i <= m; i++) if (i != y) T[x][i] /= T[x][y];
		T[x][y] = 1/T[x][y];
		for (int i = 0; i <= n; i++) if (i != x and abs(T[i][y]) > eps) {
			for (int j = 0; j <= m; j++) if (j != y) T[i][j] -= T[i][y] * T[x][j];
			T[i][y] = -T[i][y] * T[x][y];
		}
	}

	// Retorna o par (valor maximo, vetor solucao)
	pair<double, vector<double>> simplex(
			vector<vector<double>> A, vector<double> b, vector<double> c) {
		n = b.size(), m = c.size();
		T = vector(n + 1, vector<double>(m + 1));
		X = vector<int>(m);
		Y = vector<int>(n);
		for (int i = 0; i < m; i++) X[i] = i;
		for (int i = 0; i < n; i++) Y[i] = i+m;
		for (int i = 0; i < m; i++) T[0][i] = -c[i];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) T[i+1][j] = A[i][j];
			T[i+1][m] = b[i];
		}
		while (true) {
			int x = -1, y = -1;
			double mn = -eps;
			for (int i = 1; i <= n; i++) if (T[i][m] < mn) mn = T[i][m], x = i;
			if (x < 0) break;
			for (int i = 0; i < m; i++) if (T[x][i] < -eps) { y = i; break; }

			if (y < 0) return {-1e18, {}}; // sem solucao para  Ax <= b
			pivot(x, y);
		}
		while (true) {
			int x = -1, y = -1;
			double mn = -eps;
			for (int i = 0; i < m; i++) if (T[0][i] < mn) mn = T[0][i], y = i;
			if (y < 0) break;
			mn = 1e200;
			for (int i = 1; i <= n; i++) if (T[i][y] > eps and T[i][m] / T[i][y] < mn)
				mn = T[i][m] / T[i][y], x = i;

			if (x < 0) return {1e18, {}}; // c^T x eh ilimitado
			pivot(x, y);
		}
		vector<double> r(m);
		for(int i = 0; i < n; i++) if (Y[i] < m) r[Y[i]] = T[i+1][m];
		return {T[0][m], r};
	}
}
