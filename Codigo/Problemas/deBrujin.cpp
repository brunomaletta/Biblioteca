// Sequencia de de Brujin
//
// Se passar sem o terceiro parametro, gera um vetor com valores
// em [0, k) de tamanho k^n de forma que todos os subarrays ciclicos
// de tamanho n ocorrem exatamente uma vez
// Se passar com um limite lim, gera o menor vetor com valores
// em [0, k) que possui lim subarrays de tamanho n distintos
// (assume que lim <= k^n)
//
// Linear no tamanho da resposta

vector<int> de_brujin(int n, int k, int lim = INF) {
	if (k == 1) return vector<int>(lim == INF ? 1 : n, 0);
	vector<int> l = {0}, ret; // l eh lyndon word
	while (true) {
		if (l.size() == 0) {
			if (lim == INF) break;
			l.push_back(0);
		}
		if (n % l.size() == 0) for (int i : l) {
			ret.push_back(i);
			if (ret.size() == n+lim-1) return ret;
		}
		int p = l.size();
		while (l.size() < n) l.push_back(l[l.size()%p]);
		while (l.size() and l.back() == k-1) l.pop_back();
		if (l.size()) l.back()++;
	}
	return ret;
}
