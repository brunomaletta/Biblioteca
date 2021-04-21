// 2-SAT
//
// solve(n) Retorna se eh possivel atribuir valores
// pras 'n' variaveis
// ans[i] fala se a variavel 'i' eh verdadeira
// Pra chamar o negado da variavel 'i', usar ~i
//
// O(|V|+|E|)

namespace doisSAT {
#warning limpar o grafo
	vector<int> g[2*MAX];
	int vis[2*MAX], comp[2*MAX], id[2*MAX];
	stack<int> s;
	int ans[MAX];

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if (ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void tarjan(int n) {
		int t = 0;
		for (int i = 0; i < 2*n; i++) vis[i] = 0;
		for (int i = 0; i < 2*n; i++) if (!vis[i]) dfs(i, t);
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}
	void add_cl(int x, int y) { // x ou y
		add_impl(~x, y);
	}
	void add_xor(int x, int y) { // x xor y
		add_cl(x, y), add_cl(~x, ~y);
	}
	void add_eq(int x, int y) { // x = y
		add_xor(~x, y);
	}
	void add_true(int x) { // x = T
		add_impl(~x, x);
	}

	bool solve(int n) {
		for (int i = 0; i < n; i++) ans[i] = -1;
		tarjan(n);
		for (int i = 0; i < n; i++)
			if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
}
