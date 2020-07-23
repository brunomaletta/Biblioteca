// Dominator Points
//
// Se um ponto A tem ambas as coordenadas >= B, dizemos
// que A domina B
// is_dominated(p) fala se existe algum ponto no conjunto
// que domina p
// insert(p) insere p no conjunto
// (se p for dominado por alguem, nao vai inserir)
//
// Complexidades:
// is_dominated - O(log(n))
// insert - O(log(n)) amortizado

struct dominator_points {
	set<pair<int, int>> se;

	dominator_points() {}
	bool is_dominated(pair<int, int> p) {
		auto it = se.lower_bound(p);
		if (it == se.end()) return 0;
		return it->second >= p.second;
	}
	bool insert(pair<int, int> p) {
		if (is_dominated(p)) return 0;
		auto it = se.lower_bound(p);
		while (it != se.begin()) {
			it--;
			if (it->second > p.second) break;
			it = se.erase(it);
		}
		se.insert(p);
		return 1;
	}
};
