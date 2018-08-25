// Longest Increasing Subsequence
//
// Calcula uma LIS
// Para ter o tamanho basta fazer lis().size()
// Implementacao do algotitmo descrito em:
// https://goo.gl/HiFkn2
//
// O(n log(n))

const int INF = 0x3f3f3f3f;

int n, v[MAX];

vector<int> lis() {
	int I[n + 1], L[n];

	// pra BB funfar bacana
	I[0] = -INF;
	for (int i = 1; i <= n; i++) I[i] = INF;

	for (int i = 0; i < n; i++) {
		// BB
		int l = 0, r = n;
		while (l < r) {
			int m = (l + r) / 2;
			if (I[m] >= v[i]) r = m;
			else l = m + 1;
		}
                
		// ultimo elemento com tamanho l eh v[i]
		I[l] = v[i];
		// tamanho da LIS terminando com o
		// elemento v[i] eh l
		L[i] = l;
	}

	// reconstroi LIS
	vector<int> ret;
	int m = -INF, p;
	for (int i = 0; i < n; i++) if (L[i] > m) {
		m = L[i];
		p = i;
	}
	ret.push_back(v[p]);
	int last = m;
	while (p--) if (L[p] == m - 1) {
		ret.push_back(v[p]);
		m = L[p];
	}

	reverse(ret.begin(), ret.end());
	return ret;
}
