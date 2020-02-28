// Heavy-Light Decomposition - aresta
//
// SegTree de soma
// query / update de soma das arestas
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))

#define f first
#define s second

namespace seg { ... }

namespace hld {
	vector<pair<int, int> > g[MAX];
	int in[MAX], out[MAX], sz[MAX];
	int sobe[MAX], pai[MAX];
	int h[MAX], v[MAX], t;

	void build_hld(int k, int p = -1, int f = 1) {
		v[in[k] = t++] = sobe[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i.f != p) {
			sobe[i.f] = i.s; pai[i.f] = k;
			h[i.f] = (i == g[k][0] ? h[k] : i.f);
			build_hld(i.f, k, f); sz[k] += sz[i.f];

			if (sz[i.f] > sz[g[k][0].f]) swap(i, g[k][0]);
		}
		out[k] = t;
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
		build_hld(root);
		seg::build(t, v);
	}
	ll query_path(int a, int b) {
		if (a == b) return 0;
		if (in[a] < in[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(in[b]+1, in[a]);
		return seg::query(in[h[a]], in[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (a == b) return;
		if (in[a] < in[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg::update(in[b]+1, in[a], x);
		seg::update(in[h[a]], in[a], x); update_path(pai[h[a]], b, x);
	}
	ll query_subtree(int a) {
		if (in[a] == out[a]-1) return 0;
		return seg::query(in[a]+1, out[a]-1);
	}
	void update_subtree(int a, int x) {
		if (in[a] == out[a]-1) return;
		seg::update(in[a]+1, out[a]-1, x);
	}
	int lca(int a, int b) {
		if (in[a] < in[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}
