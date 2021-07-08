// Algoritmo MO - queries em caminhos de árvore
// 
// Problema que resolve: https://www.spoj.com/problems/COT2/
//
// Complexidade sendo c = O(update) e SQ = sqrt(n):
// O((n + q) * sqrt(n) * c)

const int MAX = 40010, SQ = 400;

vector<int> g[MAX];

namespace LCA { ... }

int in[MAX], out[MAX], vertex[2 * MAX];
bool on[MAX];

int dif, freq[MAX];
vector<int> w;

void dfs(int v, int p, int &t) {
	vertex[t] = v, in[v] = t++;
	for (int u : g[v]) if (u != p) 
		dfs(u, v, t);
	vertex[t] = v, out[v] = t++;
}

void update(int p) { // faça alterações aqui
	int v = vertex[p];
	if (not on[v]) { // insere vertex v
		dif += (freq[w[v]] == 0);
		freq[w[v]]++;
	}
	else { // retira o vértice v
		dif -= (freq[w[v]] == 1);
		freq[w[v]]--;
	}
	on[v] = not on[v];
}

vector<tuple<int, int, int>> build_queries(const vector<pair<int, int>>& q) {
	LCA::build(0); // qualquer algoritmo de LCA funciona
	vector<tuple<int, int, int>> ret;
	for (auto [l, r] : q){
		if (in[r] < in[l]) swap(l, r);
		int p = LCA::lca(l, r);
		int init = (p == l) ? in[l] : out[l];
		ret.emplace_back(init, in[r], in[p]);
	}
	return ret;
}

vector<int> mo_tree(const vector<pair<int, int>>& vq){
	int t = 0;
	dfs(0, -1, t);

	auto q = build_queries(vq);
	
	vector<int> ord(q.size());
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&] (int l, int r) {
		int bl = get<0>(q[l]) / SQ, br = get<0>(q[r]) / SQ;
		if (bl != br) return bl < br;
		return bl % 2 == 1 ? get<1>(q[l]) < get<1>(q[r]) : get<1>(q[l]) > get<1>(q[r]);
	});

	memset(freq, 0, sizeof freq);
	dif = 0;
	
	vector<int> ret(q.size());
	int l = 0, r = -1;
	for (int i : ord) {
		auto [ql, qr, qp] = q[i];
		while (r < qr) update(++r);
		while (l > ql) update(--l);
		while (l < ql) update(l++);
		while (r > qr) update(r--);

		if (qp < l or qp > r) { // se LCA está entre as pontas
			update(qp);
			ret[i] = dif;
			update(qp);
		}
		else ret[i] = dif;
	}
	return ret;
}
