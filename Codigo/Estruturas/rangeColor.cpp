// Range color
//
// update(l, r, c) colore o range [l, r] com a cor c,
// e retorna os ranges que foram coloridos {l, r, cor}
// query(i) returna a cor da posicao i
//
// Complexidades (para q operacoes):
// update - O(log(q)) amortizado
// query - O(log(q))

template<typename T> struct color {
	set<tuple<int, int, T>> se;

	vector<tuple<int, int, T>> update(int l, int r, T val) {
		auto it = se.upper_bound({r, INF, val});
		if (it != se.begin() and get<1>(*prev(it)) > r) {
			auto [L, R, V] = *--it;
			se.erase(it);
			se.emplace(L, r, V), se.emplace(r+1, R, V);
		}
		it = se.lower_bound({l, -INF, val});
		if (it != se.begin() and get<1>(*prev(it)) >= l) {
			auto [L, R, V] = *--it;
			se.erase(it);
			se.emplace(L, l-1, V), it = se.emplace(l, R, V).first;
		}
		vector<tuple<int, int, T>> ret;
		for (; it != se.end() and get<0>(*it) <= r; it = se.erase(it))
			ret.push_back(*it);
		se.emplace(l, r, val);
		return ret;
	}
	T query(int i) {
		auto it = se.upper_bound({i, INF, T()});
		if (it == se.begin() or get<1>(*--it) < i) return -1; // nao tem
		return get<2>(*it);
	}
};
