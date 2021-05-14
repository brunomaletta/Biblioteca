// Algoritmo Z
//
// Complexidades:
// z - O(|s|)
// match - O(|s| + |p|)

vector<int> get_z(string s) {
	int n = s.size();
	vector<int> z(n, 0);

	// intervalo da ultima substring valida
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		// estimativa pra z[i]
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		// calcula valor correto
		while (i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;
		// atualiza [l, r]
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}

	return z;
}

// quantas vezes p aparece em s
int match(string s, string p) {
	int n = s.size(), m = p.size();
	vector<int> z = get_z(p + s);

	int ret = 0;
	for (int i = m; i < n + m; i++)
		if (z[i] >= m) ret++;

	return ret;
}

