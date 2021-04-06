// Block-Cut Tree
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os blocos, e a outra cor sao os pontos de art.
// art[i] responde se i eh ponto de articulacao
// Funciona pra grafo nao conexo, e ja limpa tudo
//
// O(n+m)

vector<int> g[MAX];
stack<int> s;
int id[MAX], art[MAX], pos[MAX];
vector<vector<int>> blocks, tree;

int dfs(int i, int &t, int p = -1) {
	int lo = id[i] = t++;
	s.push(i);
	for (int j : g[i]) if (j != p) {
		if (id[j] == -1) {
			int val = dfs(j, t, i);
			lo = min(lo, val);

			if (val >= id[i]) {
				art[i]++;
				blocks.emplace_back(1, i);
				while (blocks.back().back() != j)
					blocks.back().push_back(s.top()), s.pop();
			}
			// if (val > id[i]) aresta i-j eh ponte
		}
		else lo = min(lo, id[j]);
	}
	if (p == -1 and art[i]) art[i]--;
	return lo;
}

void build(int n) {
	for (int i = 0; i < n; i++) id[i] = -1, art[i] = 0;
	blocks.clear(), tree.clear();
	while (s.size()) s.pop();
	int t = 0;

	for (int i = 0; i < n; i++) if (id[i] == -1) dfs(i, t, -1);

	tree.resize(blocks.size()); // no maximo 2*n
	for (int i = 0; i < n; i++) if (art[i])
		pos[i] = tree.size(), tree.emplace_back();

	for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
		if (!art[j]) pos[j] = i;
		else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
	}
}
