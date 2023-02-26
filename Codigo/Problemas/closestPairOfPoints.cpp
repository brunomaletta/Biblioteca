// Closest pair of points
//
// O(nlogn)

pair<pt, pt> closest_pair_of_points(vector<pt> v) {
	int n = v.size();
	sort(v.begin(), v.end());
	for (int i = 1; i < n; i++) if (v[i] == v[i-1]) return {v[i-1], v[i]};
	auto cmp_y = [&](const pt &l, const pt &r) {
		if (l.y != r.y) return l.y < r.y;
		return l.x < r.x;
	};
	set<pt, decltype(cmp_y)> s(cmp_y);
	int l = 0, r = -1;
	ll d2_min = numeric_limits<ll>::max();
	pt pl, pr;
	const int magic = 5;
	while (r+1 < n) {
		auto it = s.insert(v[++r]).first;
		int cnt = magic/2;
		while (cnt-- and it != s.begin()) it--;
		cnt = 0;
		while (cnt++ < magic and it != s.end()) {
			if (!((*it) == v[r])) {
				ll d2 = dist2(*it, v[r]);
				if (d2_min > d2) {
					d2_min = d2;
					pl = *it;
					pr = v[r];
				}
			}
			it++;
		}
		while (l < r and sq(v[l].x-v[r].x) > d2_min) s.erase(v[l++]);
	}
	return {pl, pr};
}
