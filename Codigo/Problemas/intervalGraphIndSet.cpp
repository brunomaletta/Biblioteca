// Conj. Indep. Maximo com Peso em Grafo de Intervalo
//
// Retorna os indices ordenados dos intervalos selecionados
// Se tiver empate, retorna o que minimiza o comprimento total
//
// O(n log(n))

vector<int> ind_set(vector<tuple<int, int, int>>& v) {
	vector<tuple<int, int, int>> w;
	for (int i = 0; i < v.size(); i++) {
		w.push_back(tuple(get<0>(v[i]), 0, i));
		w.push_back(tuple(get<1>(v[i]), 1, i));
	}
	sort(w.begin(), w.end());

	vector<int> nxt(v.size());
	vector<pair<ll, int>> dp(v.size());
	int last = -1;
	for (auto [fim, t, i] : w) {
		if (t == 0) {
			nxt[i] = last;
			continue;
		}
		dp[i] = {0, 0};
		if (last != -1) dp[i] = max(dp[i], dp[last]);
		pair<ll, int> pega = {get<2>(v[i]), -(get<1>(v[i]) - get<0>(v[i]) + 1)};
		if (nxt[i] != -1) pega.first += dp[nxt[i]].first, pega.second += dp[nxt[i]].second;
		if (pega > dp[i]) dp[i] = pega;
		else nxt[i] = last;
		last = i;
	}
	pair<ll, int> ans = {0, 0};
	int idx = -1;
	for (int i = 0; i < v.size(); i++) if (dp[i] > ans) ans = dp[i], idx = i;
	vector<int> ret;
	while (idx != -1) {
		if (get<2>(v[idx]) > 0 and
			(nxt[idx] == -1 or get<1>(v[nxt[idx]]) < get<0>(v[idx]))) ret.push_back(idx);
		idx = nxt[idx];
	}
	sort(ret.begin(), ret.end());
	return ret;
}
