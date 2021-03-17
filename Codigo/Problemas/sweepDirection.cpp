// Sweep Direction
//
// Passa por todas as ordenacoes dos pontos definitas por "direcoes"
// Assume que nao existem pontos coincidentes
//
// O(n^2 log n)

void sweep_direction(vector<pt> v) {
	int n = v.size();
	sort(v.begin(), v.end(), [](pt a, pt b) {
		if (a.x != b.x) return a.x < b.x;
		return a.y > b.y;
	});
	vector<int> at(n);
	iota(at.begin(), at.end(), 0);
	vector<pair<int, int>> swapp;
	for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++)
		swapp.push_back({i, j}), swapp.push_back({j, i});

	sort(swapp.begin(), swapp.end(), [&](auto a, auto b) {
		pt A = rotate90(v[a.first] - v[a.second]);
		pt B = rotate90(v[b.first] - v[b.second]);
		if (quad(A) == quad(B) and !sarea2(pt(0, 0), A, B)) return a < b;
		return compare_angle(A, B);
	});
	for (auto par : swapp) {
		assert(abs(at[par.first] - at[par.second]) == 1);
		int l = min(at[par.first], at[par.second]),
			r = n-1 - max(at[par.first], at[par.second]);
		// l e r sao quantos caras tem de cada lado do par de pontos
		// (cada par eh visitado duas vezes)
		swap(v[at[par.first]], v[at[par.second]]);
		swap(at[par.first], at[par.second]);
	}
}
