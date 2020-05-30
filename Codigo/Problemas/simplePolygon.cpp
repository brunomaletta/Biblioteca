// Simple Polygon
//
// Verifica se um poligono com n pontos eh simples
//
// O(n log n)

bool operator < (const line& a, const line& b) { // comparador pro sweepline
	if (a.p == b.p) return ccw(a.p, a.q, b.q);
	if (!eq(a.p.x, a.q.x) and (eq(b.p.x, b.q.x) or a.p.x+eps < b.p.x))
		return ccw(a.p, a.q, b.p);
	return ccw(a.p, b.q, b.p);
}

bool simple(vector<pt> v) {
	auto intersects = [&](pair<line, int> a, pair<line, int> b) {
		if ((a.s+1)%v.size() == b.s or (b.s+1)%v.size() == a.s) return false;
		return interseg(a.f, b.f);
	};
	vector<line> seg;
	vector<pair<pt, pair<int, int>>> w;
	for (int i = 0; i < v.size(); i++) {
		pt at = v[i], nxt = v[(i+1)%v.size()];
		if (nxt < at) swap(at, nxt);
		seg.push_back(line(at, nxt));
		w.push_back({at, {0, i}});
		w.push_back({nxt, {1, i}});
		// casos degenerados estranhos
		if (isinseg(v[(i+2)%v.size()], line(at, nxt))) return 0;
		if (isinseg(v[(i+v.size()-1)%v.size()], line(at, nxt))) return 0;
	}
	sort(w.begin(), w.end());
	set<pair<line, int>> se;
	for (auto i : w) {
		line at = seg[i.s.s];
		if (i.s.f == 0) {
			auto nxt = se.lower_bound({at, i.s.s});
			if (nxt != se.end() and intersects(*nxt, {at, i.s.s})) return 0;
			if (nxt != se.begin() and intersects(*(--nxt), {at, i.s.s})) return 0;
			se.insert({at, i.s.s});
		} else {
			auto nxt = se.upper_bound({at, i.s.s}), cur = nxt, prev = --cur;
			if (nxt != se.end() and prev != se.begin()
				and intersects(*nxt, *(--prev))) return 0;
			se.erase(cur);
		}
	}
	return 1;
}
