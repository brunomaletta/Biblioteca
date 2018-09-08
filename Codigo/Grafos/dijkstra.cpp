// Dijkstra
//
// encontra menor distancia de a
// para todos os vertices
// se ao final do algoritmo d[i] = INF,
// entao a nao alcanca i
//
// O(m log(n))

int n;
vector<vector<int> > g(MAX);
vector<vector<int> > w(MAX); // peso das arestas
int d[MAX];

void dijsktra(int a) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[a] = 0;
	priority_queue<pair<int, int> > Q;
	Q.push(make_pair(0, a));

	while (Q.size()) {
		int u = Q.top().second;
		if (-Q.top().first > d[u]) continue;
		Q.pop();
		

		for (int i = 0; i < (int) g[u].size(); i++) {
			int v = g[u][i];
			if (d[v] > d[u] + w[u][i]) {
				d[v] = d[u] + w[u][i];
				Q.push(make_pair(-d[v], v));
			}
		}
	}
}
