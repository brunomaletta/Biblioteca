// Max Suffix
//
// computa o indice do maior sufixo da
// string, lexicograficamente
//
// O(n)

int max_sulf(string s) {
	s += '#';
	int ans = max_element(s.begin(), s.end()) - s.begin();
	for (int i = ans+1, j = 0; i < s.size(); i++) {
		if (ans+j < i and s[i] == s[ans+j]) j++;
		else {
			if (ans+j < i and s[i] > s[ans+j]) ans = i-j;
			j = 0;
		}
	}
	return ans;
}
