// eertree
//
// Constroi a eertree, caractere a caractere
// Inicializar com a quantidade de caracteres maxima
// size() retorna a quantidade de substrings pal. distintas
// depois de chamar propagate(), cada substring palindromica
// ocorre qt[i] vezes. O propagate() retorna o numero de
// substrings pal. com repeticao
//
// O(n) amortizado, considerando alfabeto O(1)

struct eertree {
	vector<vector<int>> t;
	int n, last, sz;
	vector<int> s, len, link, qt;

	eertree(int N) {
		t = vector(N+2, vector(26, int()));
		s = len = link = qt = vector<int>(N+2);
		s[0] = -1;
		link[0] = 1, len[0] = 0, link[1] = 1, len[1] = -1;
		sz = 2, last = 0, n = 1;
	}

	void add(char c) {
		s[n++] = c -= 'a';
		while (s[n-len[last]-2] != c) last = link[last];
		if (!t[last][c]) {
			int prev = link[last];
			while (s[n-len[prev]-2] != c) prev = link[prev];
			link[sz] = t[prev][c];
			len[sz] = len[last]+2;
			t[last][c] = sz++;
		}
		qt[last = t[last][c]]++;
	}
	int size() { return sz-2; }
	ll propagate() {
		ll ret = 0;
		for (int i = n; i > 1; i--) {
			qt[link[i]] += qt[i];
			ret += qt[i];
		}
		return ret;
	}
};
