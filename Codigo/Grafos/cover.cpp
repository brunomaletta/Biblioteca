// Vertex cover
//
// Encontra o tamanho do vertex cover minimo
// Da pra alterar facil pra achar os vertices
// Parece rodar com < 2 s pra N = 90
//
// O(n * 1.38^n)

namespace cover {
	const int MAX = 96;
	vector<int> g[MAX];
	bitset<MAX> bs[MAX];
	int n;

	void add(int i, int j) {
		if (i == j) return;
		n = max({n, i+1, j+1});
		bs[i][j] = bs[j][i] = 1;
	}

	int rec(bitset<MAX> m) {
		int ans = 0;
		for (int x = 0; x < n; x++) if (m[x]) {
			bitset<MAX> comp;
			function<void(int)> dfs = [&](int i) {
				comp[i] = 1, m[i] = 0;
				for (int j : g[i]) if (m[j]) dfs(j);
			};
			dfs(x);

			int ma, deg = -1, cyc = 1;
			for (int i = 0; i < n; i++) if (comp[i]) {
				int d = (bs[i]&comp).count();
				if (d <= 1) cyc = 0;
				if (d > deg) deg = d, ma = i;
			}
			if (deg <= 2) { // caminho ou ciclo
				ans += (comp.count() + cyc) / 2;
				continue;
			}
			comp[ma] = 0;

			// ou ta no cover, ou nao ta no cover
			ans += min(1 + rec(comp), deg + rec(comp & ~bs[ma]));
		}
		return ans;
	}
	int solve() {
		bitset<MAX> m;
		for (int i = 0; i < n; i++) {
			m[i] = 1;
			for (int j = 0; j < n; j++)
				if (bs[i][j]) g[i].push_back(j);
		}
		return rec(m);
	}
}
