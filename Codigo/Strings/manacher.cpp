// Manacher
//
// manacher recebe um vetor de T e retorna o vetor com tamanho dos palindromos
// ret[2*i] = tamanho do maior palindromo centrado em i
// ret[2*i+1] = tamanho maior palindromo centrado em i e i+1
//
// Complexidades:
// manacher - O(n)
// palindrome - <O(n), O(1)>
// pal_end - O(n)

template<typename T> vector<int> manacher(const T& s) {
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
		int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1); k++;
		while (i+k <= n && i-k >= 0 && s[i+k-1] == s[i-k]) k++;
		d2[i] = --k;
		if (i+k-1 > r) l = i-k, r = i+k-1;
	}
	vector<int> ret(2*n-1);
	for (int i = 0; i < n; i++) ret[2*i] = 2*d1[i]-1;
	for (int i = 0; i < n-1; i++) ret[2*i+1] = 2*d2[i+1];
	return ret;
}

// verifica se a string s[i..j] eh palindromo
template<typename T> struct palindrome {
	vector<int> man;

	palindrome(const T& s) : man(manacher(s)) {}
	bool query(int i, int j) {
		return man[i+j] >= j-i+1;
	}
};

// tamanho do maior palindromo que termina em cada posicao
template<typename T> vector<int> pal_end(const T& s) {
	vector<int> ret(s.size());
	palindrome<T> p(s);
	ret[0] = 1;
	for (int i = 1; i < s.size(); i++) {
		ret[i] = min(ret[i-1]+2, i+1);
		while (!p.query(i-ret[i]+1, i)) ret[i]--;
	}
	return ret;
}
