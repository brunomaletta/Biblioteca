// Shortest Addition Chain
//
// Computa o menor numero de adicoes para construir
// cada valor, comecando com 1 (e podendo salvar variaveis)
// Retorna um par com a dp e o pai na arvore
// A arvore eh tao que o taminho da raiz (1) ate x
// contem os valores que devem ser criados para gerar x
// A profundidade de x na arvore eh dp[x]
// DP funciona para ateh 300, mas a arvore soh funciona
// para ateh 148

// recuperacao certa soh ateh 148 (erra para 149, 233, 298)
pair<vector<int>, vector<int>> addition_chain() {
	int MAX = 301;
	vector<int> dp(MAX), p(MAX);
	for (int n = 2; n < MAX; n++) {
		pair<int, int> val = {INF, -1};
		for (int i = 1; i < n; i++) for (int j = i; j; j = p[j])
			if (j == n-i) val = min(val, pair(dp[i]+1, i));
		tie(dp[n], p[n]) = val;
		if (n == 9) p[n] = 8;
		if (n == 149 or n == 233) dp[n]--;
	}
	return {dp, p};
}
