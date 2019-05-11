// Suffix Array Rafael
//
// O(n log^2(n))

struct suffix_array{
	string &s;
	int n;
	vector<int> p, r, aux, lcp;
	seg_tree<int, min_el> st;
	suffix_array(string &s):
		s(s), n(s.size()), p(n), r(n), aux(n), lcp(n){
			for (int i = 0; i < n; i++){
				p[i] = i;
				r[i] = s[i];
			}
			auto rank = [&](int i){
				if (i >= n) return -i;
				return r[i];
			};
			for (int d = 1; d < n; d *= 2){
				auto t = [&](int i){
					return make_pair(rank(i), rank(i+d));
				};
				sort(p.begin(), p.end(),
						[&](int &i, int &j){
						return t(i) < t(j);
						}
					);
				aux[p[0]] = 0;
				for (int i = 1; i < n; i++)
					aux[p[i]] = aux[p[i-1]] + (t(p[i]) > t(p[i-1]));
				for (int j = 0; j < n; j++) r[j] = aux[j];
				if (aux[p[n-1]] == n-1) break;
			}

			int h = 0;
			for (int i = 0; i < n; i++){
				if (r[i] == n-1){
					lcp[r[i]] = 0;
					continue;
				}
				int j = p[r[i] + 1];
				while (i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
				lcp[r[i]] = h;
				h = max(0, h-1);
			}
			st = seg_tree<int, min_el>(&lcp);
		}
	int query(int l, int r){
		return st.query(l, r);
	}
	ll distinct_substrings(){
		ll ans = p[0] + 1;
		for (int i = 1; i < n; i++)
			ans += p[i] - lcp[i-1] + 1;
		return ans;
	}
};
