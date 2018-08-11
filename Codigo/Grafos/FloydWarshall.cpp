// Floyd-Warshall
//
// encontra o menor caminho entre todo
// par de vertices e detecta ciclo negativo
// returna 1 sse ha ciclo negativo
// dist[i][i] deve ser 0
// para i != j, dist[i][j] deve ser w se ha uma aresta
// (i, j) de peso w, INF caso contrario
//
// O(n^3)

int n;
int dist[MAX][MAX];

bool floyd_warshall() {
	for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	for (int i = 0; i < n; i++)
		if (dist[i][i] < 0) return 1;

	return 0;
}
