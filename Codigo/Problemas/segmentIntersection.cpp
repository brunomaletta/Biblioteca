// Segment Intersection
//
// Verifica, dado n segmentos, se existe algum par de segmentos
// que se intersecta
//
// O(n log n)

bool operator < (const line& a, const line& b) { // comparador pro sweepline
	if (a.p == b.p) return ccw(a.p, a.q, b.q);
	if (!eq(a.p.x, a.q.x) and (eq(b.p.x, b.q.x) or a.p.x+eps < b.p.x))
		return ccw(a.p, a.q, b.p);
	return ccw(a.p, b.q, b.p);
}

bool has_intersection(vector<line> v) {
	auto intersects = [&](pair<line, int> a, pair<line, int> b) {
		return interseg(a.first, b.first);
	};
	vector<pair<pt, pair<int, int>>> w;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].q < v[i].p) swap(v[i].p, v[i].q);
		w.push_back({v[i].p, {0, i}});
		w.push_back({v[i].q, {1, i}});
	}
	sort(w.begin(), w.end());
	set<pair<line, int>> se;
	for (auto i : w) {
		line at = v[i.second.second];
		if (i.second.first == 0) {
			auto nxt = se.lower_bound({at, i.second.second});
			if (nxt != se.end() and intersects(*nxt, {at, i.second.second})) return 1;
			if (nxt != se.begin() and intersects(*(--nxt), {at, i.second.second})) return 1;
			se.insert({at, i.second.second});
		} else {
			auto nxt = se.upper_bound({at, i.second.second}), cur = nxt, prev = --cur;
			if (nxt != se.end() and prev != se.begin()
				and intersects(*nxt, *(--prev))) return 1;
			se.erase(cur);
		}
	}
	return 0;
}
