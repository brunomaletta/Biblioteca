// Min/max suffix/cyclic shift
//
// Computa o indice do menor/maior sufixo/cyclic shift
// da string, lexicograficamente
//
// O(n)

template<typename T> int max_suffix(T s, bool mi = false) {
	s.push_back(*min_element(s.begin(), s.end())-1);
	int ans = 0;
	for (int i = 1; i < s.size(); i++) {
		int j = 0;
		while (ans+j < i and s[i+j] == s[ans+j]) j++;
		if (s[i+j] > s[ans+j]) {
			if (!mi or i != s.size()-2) ans = i;
		} else if (j) i += j-1;
	}
	return ans;
}

template<typename T> int min_suffix(T s) {
	for (auto& i : s) i *= -1;
	s.push_back(*max_element(s.begin(), s.end())+1);
	return max_suffix(s, true);
}

template<typename T> int max_cyclic_shift(T s) {
	int n = s.size();
	for (int i = 0; i < n; i++) s.push_back(s[i]);
	return max_suffix(s);
}

template<typename T> int min_cyclic_shift(T s) {
	for (auto& i : s) i *= -1;
	return max_cyclic_shift(s);
}
