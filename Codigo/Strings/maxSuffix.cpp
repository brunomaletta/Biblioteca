// Max Suffix
//
// computa o indice do maior sufixo da
// string, lexicograficamente
//
// O(n)

int max_suf(string s) {
	s += '$'; // precisa ser menor que os outros
	int ans = 0;
	for (int i = 1; i < s.size(); i++) {
		int j = 0;
		while (ans+j < i and s[i+j] == s[ans+j]) j++;
		if (ans+j < i and s[i+j] > s[ans+j]) ans = i;
		else if (j) i += j-1;
	}
	return ans;
}
