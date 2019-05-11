// Algoritmo de Dinic para fluxo maximo
//
// tem que definir o tamanho de g e de lev como o numero
// de vertices do grafo e depois char o a funcao fluxo
//
// Complexidade:
// Caso geral: O(V^2 * E)
// Grafo bipartido O(sqrt(V)*E)

#define INF 0x3f3f3f3f

struct edge{
	int p, c, id; // destino, capacidade, id
	edge() {p = c = id = 0;}
	edge(int p, int c, int id):p(p), c(c), id(id){}
};

vector<vector<edge> > g; // define o tamanho depois
vector <int> lev;

void add(int a, int b, int c){
	// de a para b com capacidade c
	edge d = {b, c, (int) g[b].size()};
	edge e = {a, 0, (int) g[a].size()};
	g[a].pb(d);
	g[b].pb(e);
}

bool bfs(int s, int t){
	// bfs de s para t construindo o level
	for(int i = 0; i < g.size(); i++)
		lev[i] = -1;
	lev[s] = 0;

	// bfs saindo de s
	queue <int> q;
	q.push(s);
	while(q.size()){
		int u = q.front(); q.pop();

		for(int i = 0; i < g[u].size(); i++){
			edge e = g[u][i];
			// se ja foi visitado ou nao tem capacidade nao visita
			if(lev[e.p] != -1 || !e.c) continue;
			lev[e.p] = lev[u] + 1;
			if(e.p == t) return true;
			q.push(e.p);
		}
	}

	return false;
}

int dfs(int v, int s, int f){
	if(v == s || !f) return f;

	int flu = f;
	for(int i = 0; i < g[v].size(); i++){
		edge e = g[v][i]; int u = e.p;

		// visita se tiver capacidadade e se ta no proximo nivel
		if(lev[u] != lev[v] + 1 || !e.c) continue;

		int tenta = dfs(u, s, min(flu, e.c));
		// se passou alguma coisa altera as capacidades
		if(tenta){
			flu -= tenta;
			g[v][i].c -= tenta;
			g[u][e.id].c += tenta;
		}
	}

	// se passou tudo tira da lista dos possiveis
	if(flu == f) lev[v] = -1;
	return f - flu;
}

int fluxo(int s, int t){
	int r = 0;
	while(bfs(s, t)) r += dfs(s, t, INF);
	return r;
}

// ja tem ate o debug
void imprime(){
	for(int i = 0; i < g.size(); i++){
		printf("%i -> ", i);
		for(int j = 0; j < g[i].size(); j++)
			printf("(%i %i)", g[i][j].p, g[i][j].c);
		printf("\n");
	}
	printf("\n");
}
