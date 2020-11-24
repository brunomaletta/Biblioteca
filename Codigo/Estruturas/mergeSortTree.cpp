// MergeSort Tree
//
// Se for construida sobre um array:
//		query(i, j, a, b) retorna quantos
//		elementos de v[i..j] pertencem a [a, b]
//		report(i, j, a, b) retorna os indices dos
//		elementos de v[i..j] que pertencem a [a, b]
//		retorna o vetor ordenado
// Se for construida sobre pontos (x, y):
//		query(x1, x2, y1, x2) retorna quantos pontos
//		pertencem ao retangulo (x1, y1), (x2, y2)
//		report(x1, x2, y1, y2) retorna os indices dos pontos que
//		pertencem ao retangulo (x1, y1), (x2, y2)
//		retorna os pontos ordenados lexicograficamente
//		(assume x1 <= x2, y1 <= y2)
//
// Usa O(n log(n)) de memoria
//
// Complexidades:
// construir - O(n log(n))
// query - O(log(n))
// report - O(log(n) + k) para k indices retornados

template <typename T = int> struct ms_tree {
	vector<tuple<T, T, int>> v;
	int n;
	vector<vector<tuple<T, int, int>>> t; // {y, idx, left}
	vector<T> vy;

	ms_tree(vector<pair<T, T>>& vv) : n(vv.size()), t(4*n), vy(n) {
		for (int i = 0; i < n; i++) v.push_back({vv[i].first, vv[i].second, i});
		sort(v.begin(), v.end());
		build(1, 0, n-1);
		for (int i = 0; i < n; i++) vy[i] = get<0>(t[1][i+1]);
	}
	ms_tree(vector<T>& vv) {
		vector<pair<T, T>> v2;
		for (int i = 0; i < vv.size(); i++) v2.push_back({i, vv[i]});
		*this = ms_tree(v2);
	}
	void build(int p, int l, int r) {
		t[p].push_back({get<0>(v[l]), get<0>(v[r]), 0}); // {min_x, max_x, 0}
		if (l == r) return t[p].push_back({get<1>(v[l]), get<2>(v[l]), 0});
		int m = (l+r)/2;
		build(2*p, l, m), build(2*p+1, m+1, r);

		int L = 0, R = 0;
		while (t[p].size() <= r-l+1) {
			int left = get<2>(t[p].back());
			if (L > m-l or (R+m+1 <= r and t[2*p+1][1+R] < t[2*p][1+L])) {
				t[p].push_back(t[2*p+1][1 + R++]);
				get<2>(t[p].back()) = left;
				continue;
			}
			t[p].push_back(t[2*p][1 + L++]);
			get<2>(t[p].back()) = left+1;
		}
	}

	int get_l(T y) { return lower_bound(vy.begin(), vy.end(), y) - vy.begin(); }
	int get_r(T y) { return upper_bound(vy.begin(), vy.end(), y) - vy.begin(); }

	int query(T x1, T x2, T y1, T y2) {
		function<int(int, int, int)> dfs = [&](int p, int l, int r) {
			if (l == r or x2 < get<0>(t[p][0]) or get<1>(t[p][0]) < x1) return 0;
			if (x1 <= get<0>(t[p][0]) and get<1>(t[p][0]) <= x2) return r-l;
			int nl = get<2>(t[p][l]), nr = get<2>(t[p][r]);
			return dfs(2*p, nl, nr) + dfs(2*p+1, l-nl, r-nr);
		};
		return dfs(1, get_l(y1), get_r(y2));
	}
	vector<int> report(T x1, T x2, T y1, T y2) {
		vector<int> ret;
		function<void(int, int, int)> dfs = [&](int p, int l, int r) {
			if (l == r or x2 < get<0>(t[p][0]) or get<1>(t[p][0]) < x1) return;
			if (x1 <= get<0>(t[p][0]) and get<1>(t[p][0]) <= x2) {
				for (int i = l; i < r; i++) ret.push_back(get<1>(t[p][i+1]));
				return;
			}
			int nl = get<2>(t[p][l]), nr = get<2>(t[p][r]);
			dfs(2*p, nl, nr), dfs(2*p+1, l-nl, r-nr);
		};
		dfs(1, get_l(y1), get_r(y2));
		return ret;
	}
};
