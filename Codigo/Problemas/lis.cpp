// LIS - recupera
// 
// Calcula e retorna uma LIS
//
// O(n.log(n))

template<typename T> vector<T> lis(vector<T>& v) {
	int n = v.size(), m = -1;
	vector<T> d(n+1, INF);
	vector<int> l(n);
	d[0] = -INF;

	for (int i = 0; i < n; i++) {
		// Para non-decreasing use upper_bound()
		int t = lower_bound(d.begin(), d.end(), v[i]) - d.begin();
		d[t] = v[i], l[i] = t, m = max(m, t);
	}

	int p = n;
	vector<T> ret;
	while (p--) if (l[p] == m) {
		ret.push_back(v[p]);
		m--;
	}
	reverse(ret.begin(),ret.end());

	return ret;
}
