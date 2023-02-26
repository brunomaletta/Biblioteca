// Floyd-Warshall
//
// encontra o menor caminho entre todo
// par de vertices e detecta ciclo negativo
// returna 1 sse ha ciclo negativo
// d[i][i] deve ser 0
// para i != j, d[i][j] deve ser w se ha uma aresta
// (i, j) de peso w, INF caso contrario
//
// O(n^3)

int n;
int d[MAX][MAX];

bool floyd_warshall() {
	for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	for (int i = 0; i < n; i++)
		if (d[i][i] < 0) return 1;

	return 0;
}
