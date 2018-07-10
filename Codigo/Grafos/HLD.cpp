// Heavy-Light Decomposition
// By BM
//
// SegTree de maximo, 0-based
// query_hld(u, v) calcula maior aresta
// de u para v
// update_hld muda o peso de uma aresta
// 
// SegTree pode ser facilmente modificada
//
// Complexidades:
// build_hld - O(n)
// query_hld - O(log^2 (n))
// update_hld - O(log(n))

const int INF = 0x3f3f3f3f;

int n, a, b, x; // [a, b] usado na seg tree | x : valor de update

vector<vector<pair<int, int> > > g(MAX); // (para, custo)
vector<vector<int> > ind(MAX); // index da aresta
int vis[MAX];

int subsize[MAX]; // tamanho da sub-arvore
int pai[MAX]; // pai de cada vertice
int chain[MAX]; // chain de cada vertice
int head[MAX]; // cabeca de cada chain
int num[MAX]; // numeracao do vertice na segtree
int ponta[MAX]; // vertice de baixo da aresta i
int chains; // numero de chains

int pos; // posicao atual na seg tree (na hora de montar a HLD)
int vec[MAX]; // vec[i] : custo para ir de do vertice (i) para (i - 1) (subir 1)
int seg[4 * MAX];

// proximas 3 funcoes sao funcoes normais de SegTree 0-based

int build_seg(int p, int l, int r) {
	if (l == r) return seg[p] = vec[l];

	int m = (l + r) / 2;
	return seg[p] = max(build_seg(2 * p + 1, l, m),
			build_seg(2 * p + 2, m + 1, r));
}

int query_seg(int p, int l, int r) {
	// to totalmente dentro
	if (l >= a and r <= b) return seg[p];
	// to fora
	if (r < a or l > b) return -INF;

	int m = (l + r) / 2;
	return max(query_seg(2 * p + 1, l, m),
			query_seg(2 * p + 2, m + 1, r));
}

int update_seg(int p, int l, int r) {
	// cheguei
	if (l == a and r == a) return seg[p] = x;
	// to fora
	if (r < a or l > b) return seg[p];

	int m = (l + r) / 2;
	return seg[p] = max(update_seg(2 * p + 1, l, m),
			update_seg(2 * p + 2, m + 1, r));
}

void dfs(int k) {
	vis[k] = 1;
	subsize[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (!vis[g[k][i].first]) {
			dfs(g[k][i].first);

			pai[g[k][i].first] = k;
			subsize[k] += subsize[g[k][i].first];
			ponta[ind[k][i]] = g[k][i].first;
		}
}

void hld(int k, int custo) {
	vis[k] = 1;
	chain[k] = chains - 1;

	num[k] = pos;
	vec[pos++] = custo;

	// acha filho pesado
	int f = -1, peso = -INF, prox_custo;
	for (int i = 0; i < (int) g[k].size(); i++) if (!vis[g[k][i].first])
		if (subsize[g[k][i].first] > peso) {
			f = g[k][i].first;
			peso = subsize[f];
			prox_custo = g[k][i].second;
		}

	// folha
	if (f == -1) return;

	// continua a chain
	hld(f, prox_custo);

	// comeca novas chains
	for (int i = 0; i < (int) g[k].size(); i++) if (!vis[g[k][i].first])
		if (g[k][i].first != f) {
			chains++;
			head[chains - 1] = g[k][i].first;
			hld(g[k][i].first, g[k][i].second);
		}
}

void build_hld(int root) {
	for (int i = 0; i < n; i++) vis[i] = 0;

	// DFS para calcular tamanho das sub-arvores
	// e ponta das arestas
	dfs(root);

	for (int i = 0; i < n; i++) vis[i] = 0;

	// comeca chain 0 da root
	chains = 1;
	head[0] = root;
	pos = 0;
	hld(root, -1);

	// cria seg tree
	build_seg(0, 0, n - 1);
}

// maior aresta de u para v
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
	if (num[u] < num[v]) swap(u, v);

	a = num[v] + 1, b = num[u];
	ret = max(ret, query_seg(0, 0, n - 1));

	return ret;
}

// muda o peso da aresta 'p' para 'val'
void update_hld(int p, int val) {
	x = val;
	a = b = num[ponta[p]];
	update_seg(0, 0, n - 1);
}