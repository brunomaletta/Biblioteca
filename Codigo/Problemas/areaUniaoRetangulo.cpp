// Area da Uniao de Retangulos
//
// O(n log(n))
// 5d8d2f

namespace seg {
	pair<int, ll> seg[4*MAX];
	ll lazy[4*MAX], *v;
	int n;
 
	pair<int, ll> merge(pair<int, ll> l, pair<int, ll> r){
		if (l.second == r.second) return {l.first+r.first, l.second};
		else if (l.second < r.second) return l;
		else return r;
	}
 
	pair<int, ll> build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = {1, v[l]};
		int m = (l+r)/2;
		return seg[p] = merge(build(2*p, l, m), build(2*p+1, m+1, r));
	}
	void build(int n2, ll* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p].second += lazy[p];
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	pair<int, ll> query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return {0, LINF};
		int m = (l+r)/2;
		return merge(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
	}
	pair<int, ll> update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = merge(update(a, b, x, 2*p, l, m),
				update(a, b, x, 2*p+1, m+1, r));
	}
};
 
ll seg_vec[MAX];
 
ll area_sq(vector<pair<pair<int, int>, pair<int, int>>> &sq){
	vector<pair<pair<int, int>, pair<int, int>>> up;
	for (auto it : sq){
		int x1, y1, x2, y2;
		tie(x1, y1) = it.first;
		tie(x2, y2) = it.second;
		up.push_back({{x1+1,  1}, {y1, y2}});
		up.push_back({{x2+1, -1}, {y1, y2}});
	}
	sort(up.begin(), up.end());
	memset(seg_vec, 0, sizeof seg_vec);
	ll H_MAX = MAX;
	seg::build(H_MAX-1, seg_vec);
	auto it = up.begin();
	ll ans = 0;
	while (it != up.end()){
		ll L = (*it).first.first;
		while (it != up.end() && (*it).first.first == L){
			int x, inc, y1, y2;
			tie(x, inc) = it->first;
			tie(y1, y2) = it->second;
			seg::update(y1+1, y2, inc);
			it++;
		}
		if (it == up.end()) break;
		ll R = (*it).first.first;
 
		ll W = R-L;
		auto jt = seg::query(0, H_MAX-1);
		ll H = H_MAX - 1;
		if (jt.second == 0) H -= jt.first;
		ans += W*H;
	}
	return ans;
}
