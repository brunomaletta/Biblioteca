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
	vector<pair<pt, ii>> swapp;
	for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) {
		pt a = v[i], b = v[j];
		swapp.push_back({rotate90(b-a), {i, j}});
		swapp.push_back({rotate90(a-b), {i, j}});
	}
	sort(swapp.begin(), swapp.end(), [](pair<pt, ii> a, pair<pt, ii> b) {
		if (quad(a.f) == quad(b.f) and !sarea2(pt(0, 0), at.f, b.f))
			return a.s < b.s;
		return compare_angle(a.f, b.f);
	});
	for (auto i : swapp) {
		auto par = i.s;
		assert(abs(at[par.f] - at[par.s]) == 1);
		int l = min(at[par.f], at[par.s]), r = n-1 - max(at[par.f], at[par.s]);
		// l e r são quantos caras tem de cada lado do par de pontos
		// (cada par eh visitado duas vezes)
		swap(v[at[par.f]], v[at[par.s]]);
		swap(at[par.f], at[par.s]);
	}
}
