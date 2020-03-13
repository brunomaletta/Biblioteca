// Conectividade Dinamica 2
//
// Offline com link-cut trees
// O(n log(n))

namespace lct { ... }

void dyn_conn() {
	int n, q; cin >> n >> q;
	vector<int> p(2*q, -1); // outra ponta do intervalo
	for (int i = 0; i < n; i++) lct::make_tree(i);
	vector<ii> qu(q);
	map<ii, int> m;
	for (int i = 0; i < q; i++) {
		char c; cin >> c;
		if (c == '?') continue;
		int a, b; cin >> a >> b; a--, b--;
		if (a > b) swap(a, b);
		qu[i] = {a, b};
		if (c == '+') {
			p[i] = i+q, p[i+q] = i;
			m[make_pair(a, b)] = i;
		} else {
			int j = m[make_pair(a, b)];
			p[i] = j, p[j] = i;
		}
	}
	int ans = n;
	for (int i = 0; i < q; i++) {
		if (p[i] == -1) {
			cout << ans << endl; // numero de comp conexos
			continue;
		}
		int a = qu[i].f, b = qu[i].s;
		if (p[i] > i) { // +
			if (lct::conn(a, b)) {
				int mi = lct::query(a, b);
				if (p[i] < mi) {
					p[p[i]] = p[i];
					continue;
				}
				lct::cut(qu[p[mi]].f, qu[p[mi]].s), ans++;
				p[mi] = mi;
			}
			lct::link(a, b, p[i]), ans--;
		} else if (p[i] != i) lct::cut(a, b), ans++; // -
	}
}
