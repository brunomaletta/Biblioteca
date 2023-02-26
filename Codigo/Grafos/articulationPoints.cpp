// Articulation Points
//
// Computa os pontos de articulacao (vertices criticos) de um grafo
//
// art[i] armazena o numero de novas componentes criadas ao deletar vertice i
// se art[i] >= 1, entao vertice i eh ponto de articulacao
// 
// O(n+m)

int n;
vector<vector<int>> g;
stack<int> s;
vector<int> id, art;

int dfs_art(int i, int& t, int p = -1) {
	int lo = id[i] = t++;
	s.push(i);
	for (int j : g[i]) if (j != p) {
		if (id[j] == -1) {
			int val = dfs_art(j, t, i);
			lo = min(lo, val);

			if (val >= id[i]) {
				art[i]++;
				while (s.top() != j) s.pop();
				s.pop();
			}
			// if (val > id[i]) aresta i-j eh ponte
		}
		else lo = min(lo, id[j]);
	}
	if (p == -1 and art[i]) art[i]--;
	return lo;
}

void compute_art_points() {
	id = vector<int>(n, -1);
	art = vector<int>(n, 0);
	int t = 0;
	for (int i = 0; i < n; i++) if (id[i] == -1) 
		dfs_art(i, t, -1);
}

