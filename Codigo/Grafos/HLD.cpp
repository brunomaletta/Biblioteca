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

#define f first
#define s second

vector<vector<pair<int, int> > > g(MAX);
int in[MAX], out[MAX], sz[MAX];
int sobe[MAX], pai[MAX];
int head[MAX], v[MAX], t;

// seg tree sobre o vetor v de tamanho t
void build_seg();
int query_seg(int a, int b);
void update_seg(int p, int x);

void hld(int k, int p = -1, int f = 1) {
	sz[k] = 1; v[in[k] = t++] = sobe[k];
	for (auto& i : g[k]) if (i.f != p) {
		sobe[i.f] = i.s; pai[i.f] = k;
		head[i.f] = (i == g[k][0] ? head[k] : i.f);
		hld(i.f, k, f); sz[k] += sz[i.f];

		if (sz[i.f] > sz[g[k][0].f]) swap(i, g[k][0]);
	}
	out[k] = t;
	if (p*f == -1) hld(head[k] = k, -1, t = 0);
}

void build(int root = 0) {
	t = 0;
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
