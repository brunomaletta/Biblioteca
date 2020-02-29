// Manacher
//
// manacher recebe um vetor de T e retorna o vetor com tamanho dos palíndromos
// ret[2*i] = maior palíndromo centrado em i
// ret[2*i+1] = maior palíndromo centrado em i e i+1
//
// O(n)

template<typename T> vector<int> manacher(const vector<T> &s) {
	int l = 0, r = -1, n = s.size();
	vector<int> d1(n), d2(n);
	for (int i = 0; i < n; i++) {
		int k = i > r ? 1 : min(d1[l+r-i], r-i);
		while (i+k < n && i-k >= 0 && s[i+k] == s[i-k]) k++;
		d1[i] = k--;
		if (i+k > r) l = i-k, r = i+k; 
	}
	l = 0, r = -1;
	for (int i = 0; i < n; i++) {
		int k = (i > r ? 0 : min(d2[l+r-i+1], r-i+1)) + 1;
		while (i+k <= n && i-k >= 0 && s[i+k-1] == s[i-k]) k++;
		d2[i] = --k;
		if (i+k-1 > r) l = i-k, r = i+k-1;
	}
	vector<int> ret;
	ret.resize(2*n);
	for (int i = 0; i < n; i++)
		ret.push_back(2*d1[i]), ret.push_back(2*d2[i] - 1);
	return ret;
}

