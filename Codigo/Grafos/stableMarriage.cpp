// Stable Marriage
//
// Emparelha todos os elementos de A com elementos de B 
// de forma que nao exista um par x \in A, y \in B 
// e x nao pareado com y tal que x prefira parear com y
// e y prefira parear com x.
// 
// a[i] contem os elementos de B ordenados por preferencia de i
// b[j] contem os elementos de A ordenados por preferencia de j
// |A| <= |B|
//
// Retorna um vetor v de tamanho |A| onde v[i] guarda o match de i.
//
// O(|A| * |B|)

vector<int> stable_marriage(vector<vector<int>> &a, vector<vector<int>> &b) {
	int n = a.size(), m = b.size();
	assert(a[0].size() == m and b[0].size() == n and n <= m);
	vector<int> match(m, -1), it(n, 0);
	vector inv_b(m, vector<int>(n));
	for (int i = 0; i < m; i++) for (int j = 0; j < n; j++)
		inv_b[i][b[i][j]] = j;

	queue<int> q;
	for (int i = 0; i < n; i++) q.push(i);
	while (q.size()) {
		int i = q.front(); q.pop();
		int j = a[i][it[i]];

		if (match[j] == -1) match[j] = i;
		else if (inv_b[j][i] < inv_b[j][match[j]]) {
			q.emplace(match[j]);
			it[match[j]]++;
			match[j] = i;
		} else q.emplace(i), it[i]++;
	}

	vector<int> ret(n);
	for (int i = 0; i < m; i++) if (match[i] != -1) ret[match[i]] = i;
	return ret;
}
