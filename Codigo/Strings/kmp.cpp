// KMP
//
// Primeiro chama a funcao process com o padrao
// Depois chama match com (texto, padrao)
// Vai retornar o numero de ocorrencias do padrao
// p eh 1-based
//
// Complexidades:
// process - O(m)
// match - O(n + m)
// n = |texto| e m = |padrao|

int p[MAX];

void process(string& s) {
	int i = 0, j = -1;
	p[0] = -1;
	while (i < s.size()) {
		while (j >= 0 and s[i] != s[j]) j = p[j];
		i++, j++;
		p[i] = j;
	}
}

int match(string& s, string& t) {
	process(t);
	int i = 0, j = 0, ans = 0;
	while (i < s.size()) {
		while (j >= 0 and s[i] != t[j]) j = p[j];
		i++, j++;
		if (j == t.size()) j = p[j], ans++;
	}
	return ans;
}
