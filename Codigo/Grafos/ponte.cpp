//Codigo para deteccao de pontes
//
//Tudo 0-based, deixa o grafo direcionado em g
//Chama zera(numDeVertices)
//Depois dfs para (0, -1) = (verticeInicial, paiDele)
//Se tiver ponte a variavel ok vai ser 0 no final
//
//Complexidade: O(n + m)

vector <vector<int> > g(N);
vector<int> di (N);
vector<int> lo (N);
vector<int> vi (N);
int d, ok;

void zera(int n){
	for(int i = 0; i < n; i++){
		g[i].clear();
		di[i] = -1;
		lo[i] = INF;
		vi[i] = 0;
	}
	ok = 1;
	d = 0;
}

void dfs(int v, int pai){
	vi[v] = 1;
	//ele eh o d-esimo a ser visitado e alcanca o d-esimo vertice
	di[v] = lo[v] = d++;

	for(int i = 0; i < g[v].size(); i++){
		int u = g[v][i];
		if(!vi[u])
			dfs(u, v);

		//o filho nao alcanca ninguem menor ou igual a ele, eh ponte
		if(di[v] < lo[u])
			ok = 0;

		//atualiza o menor que ele alcanca
		if(pai != u && lo[u] < lo[v])
			lo[v] = lo[u];
	}
}
