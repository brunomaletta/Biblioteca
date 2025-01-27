// Minkowski Sum
//
// Computa A+B = {a+b : a \in A, b \in B}, em que
// A e B sao poligonos convexos
// A+B eh um poligono convexo com no max |A|+|B| pontos
//
// O(|A|+|B|)

vector<pt> minkowski(vector<pt> p, vector<pt> q) {
	auto fix = [](vector<pt>& P) {
		rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
		P.push_back(P[0]), P.push_back(P[1]);
	};
	fix(p), fix(q);
	vector<pt> ret;
	int i = 0, j = 0;
	while (i < p.size()-2 or j < q.size()-2) {
		ret.push_back(p[i] + q[j]);
		auto c = ((p[i+1] - p[i]) ^ (q[j+1] - q[j]));
		if (c >= 0) i = min<int>(i+1, p.size()-2);
		if (c <= 0) j = min<int>(j+1, q.size()-2);
	}
	return ret;
}

ld dist_convex(vector<pt> p, vector<pt> q) {
	for (pt& i : p) i = i * -1;
	auto s = minkowski(p, q);
	if (inpol(s, pt(0, 0))) return 0;
	ld ans = DINF;
	for (int i = 0; i < s.size(); i++) ans = min(ans,
			disttoseg(pt(0, 0), line(s[(i+1)%s.size()], s[i])));
	return ans;
}
