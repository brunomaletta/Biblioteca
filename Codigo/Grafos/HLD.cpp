// Heavy-Light Decomposition
//
// SegTree de maximo
// query_path(a, b) calcula maior aresta
// no caminho de a pra b
// query_subtree(a) calcula maior aresta
// na subarvore dos filhos de a (inclusive)
// update(p, val) muda o peso da aresta
// que vai de p para o pai de p para val
// 
// SegTree pode ser facilmente modificada
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// query_subtree - O(log(n))
// update - O(log(n))

vector<vector<int> > g(MAX), w(MAX);
int in[MAX], out[MAX], sz[MAX];
int sobe[MAX], pai[MAX];
int head[MAX], v[MAX], t;

// seg tree sobre o vetor v de tamanho t
void build_seg();
int query_seg(int a, int b);
void update_seg(int p, int x);

int dfs(int k, int p = -1) {
	sz[k] = 1;
	for (int i = 0; i < g[k].size(); i++) if (g[k][i] != p){
		sobe[g[k][i]] = w[k][i]; pai[g[k][i]] = k;
		sz[k] += dfs(g[k][i], k);

		if (sz[g[k][i]] > sz[g[k][0]])
			swap(g[k][i], g[k][0]), swap(w[k][i], w[k][0]);
	}
	return sz[k];
}

void hld(int k, int p = -1) {
	v[in[k] = t++] = sobe[k];
	for (int i : g[k]) if (i != p) {
		head[i] = (i == g[k][0] ? head[k] : i);
		hld(i, k);
	}
	out[k] = t;
}

void build(int root = 0) {
	head[root] = root;
	dfs(root);
	hld(root);
	build_seg();
}

int query_path(int a, int b) {
	if (a == b) return -INF;
	if (in[a] < in[b]) swap(a, b);

	if (head[a] == head[b]) return query_seg(in[b]+1, in[a]);
	return max(query_seg(in[head[a]], in[a]), query_path(pai[head[a]], b));
}

int query_subtree(int a) {
	if (in[a] == out[a]-1) return -INF;;
	return query_seg(in[a]+1, out[a]-1);
}

void update(int p, int val) {
	update_seg(in[p], val);
}
