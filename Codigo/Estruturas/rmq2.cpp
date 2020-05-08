// RMQ <O(n), O(1)> - cartesian tree
//
// O(n) pra buildar, query O(1)
// Para retornar o indice, basta
// trocar v[...] para ... na query

template<typename T> struct rmq {
	vector<T> v;
	int n, b;
	vector<int> id, st;
	vector<vector<int>> table;
	vector<vector<vector<int>>> entre;

	int op(int x, int y) { return v[x] < v[y] ? x : y; }
	rmq(vector<T>& v_) {
		v = v_, n = v.size();
		b = (__builtin_clz(1)-__builtin_clz(n)+1)/4 + 1;
		id.resize(n);
		table.assign(4*b, vector<int>((n+b-1)/b));
		entre.assign(1<<b<<b, vector<vector<int>>(b, vector<int>(b, -1)));
		for (int i = 0; i < n; i += b) {
			int at = 0, l = min(n, i+b);
			st.clear();
			for (int j = i; j < l; j++) {
				while (st.size() and op(st.back(), j) == j) st.pop_back(), at *= 2;
				st.push_back(j), at = 2*at+1;
			}
			for (int j = i; j < l; j++) id[j] = at;
			if (entre[at][0][0] == -1) for (int x = 0; x < l-i; x++) {
				entre[at][x][x] = x;
				for (int y = x+1; y < l-i; y++)
					entre[at][x][y] = op(i+entre[at][x][y-1], i+y) - i;
			}
			table[0][i/b] = i+entre[at][0][l-i-1];
		}
		for (int j = 1; (1<<j) <= (n+b-1)/b; j++)
			for (int i = 0; i+(1<<j) <= (n+b-1)/b; i++)
				table[j][i] = op(table[j-1][i], table[j-1][i+(1<<(j-1))]);
	}
	T query(int i, int j) {
		if (i/b == j/b) return v[i/b*b+entre[id[i]][i%b][j%b]];
		int x = i/b+1, y = j/b-1, ans = i;
		if (x <= y) {
			int t = __builtin_clz(1) - __builtin_clz(y-x+1);
			ans = op(ans, op(table[t][x], table[t][y-(1<<t)+1]));
		}
		ans = op(ans, op(i/b*b+entre[id[i]][i%b][b-1], j/b*b+entre[id[j]][0][j%b]));
		return v[ans];
	}
};
