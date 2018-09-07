// Heavy-Light Decomposition
//
// SegTree de maximo, 0-based
// query_hld(u, v) calcula maior aresta
// no caminho de u pra v
// update_hld(p, val) muda o peso da aresta
// p para val
// 
// SegTree pode ser facilmente modificada
//
// Complexidades:
// build_hld - O(n)
// query_hld - O(log^2 (n))
// update_hld - O(log(n))

int n, a, b, x; // [a, b] usado na seg tree | x : valor de update
vector<vector<int> > g(MAX), w(MAX);
int subsize[MAX]; // tamanho da sub-arvore
int pai[MAX], chain[MAX], head[MAX]; // cabeca de cada chain
int num[MAX]; // numeracao do vertice na segtree
int vec[MAX]; // v[i] : custo de u para pai[u], u = num[i]
vector<vector<int> > ind(MAX); // index da aresta
int ponta[MAX]; // vertice de baixo da aresta
int vis[MAX], chains, seg[4 * MAX];
int pos; // posicao atual na seg tree (na hora de montar a HLD)

// seg tree de maximo com update pontual
int build_seg(int p, int l, int r);
int query_seg(int p, int l, int r);
int update_seg(int p, int l, int r);

void dfs(int k) {
	vis[k] = 1;
	subsize[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++) {
		int u = g[k][i];
		if (!vis[u]) {
			dfs(u);

			pai[u] = k;
			subsize[k] += subsize[u];
			ponta[ind[k][i]] = u;
		}
	}
}

void hld(int k, int custo) {
	vis[k] = 1;
	chain[k] = chains - 1;

	num[k] = pos;
	vec[pos++] = custo;

	// acha filho pesado
	int f = -1, peso = -INF, prox_custo;
	for (int i = 0; i < (int) g[k].size(); i++) if (!vis[g[k][i]])
		if (subsize[g[k][i]] > peso) {
			f = g[k][i];
			peso = subsize[f];
			prox_custo = w[k][i];
		}

	// folha
	if (f == -1) return;

	// continua a chain
	hld(f, prox_custo);

	// comeca novas chains
	for (int i = 0; i < (int) g[k].size(); i++)
		if (!vis[g[k][i]] and g[k][i] != f) {
			chains++;
			head[chains - 1] = g[k][i];
			hld(g[k][i], w[k][i]);
		}
}

void build_hld(int root) {
	for (int i = 0; i < n; i++) vis[i] = 0;

	// DFS pra calcular tamanho das sub-arvores,
	// e ponta das arestas
	dfs(root);

	for (int i = 0; i < n; i++) vis[i] = 0;

	// comeca 0 chain da root
	chains = 1;
	head[0] = root;
	pos = 0;
	hld(root, -1);

	// cria seg tree
	build_seg(0, 0, n - 1);
}

int query_hld(int u, int v) {
	if (u == v) return 0;

	int ret = -INF;

	while (chain[u] != chain[v]) {
		// sobe o de maior chain
		if (chain[u] < chain[v]) swap(u, v);

		a = num[head[chain[u]]], b = num[u];
		ret = max(ret, query_seg(0, 0, n - 1));

		u = head[chain[u]];
		u = pai[u];
	}

	if (u == v) return ret;

	// query final
	if (num[u] < num[v]) swap(u, v); // LCA eh v

	a = num[v] + 1, b = num[u];
	ret = max(ret, query_seg(0, 0, n - 1));

	return ret;
}

void update_hld(int p, int val) {
	x = val;
	a = b = num[ponta[p]];
	update_seg(0, 0, n - 1);
}
