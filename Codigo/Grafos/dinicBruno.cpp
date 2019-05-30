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
}

bool bfs(int s, int t){
}

int dfs(int v, int s, int f){
}

int fluxo(int s, int t){
}

// ja tem ate o debug
void imprime(){
}
