// 2-SAT
//
// Retorna se eh possivel atribuir valores
// Grafo tem que caber 2n vertices
// add(x, y) adiciona implicacao x -> y
// Para adicionar uma clausula (x ou y)
// chamar add(nao(x), y)
// Se x tem que ser verdadeiro, chamar add(nao(x), x)
// O tarjan deve computar o componente conexo
// de cada vertice em comp
//
// O(|V|+|E|)

vector<int> g[MAX];
int n;

int nao(int x){ return (x + n) % (2*n); }

// x -> y  =  !x ou y
void add(int x, int y){
	g[x].pb(y);
	// contraposicao
	g[nao(y)].pb(nao(x));
}

bool doisSAT(){
	tarjan();
	for (int i = 0; i < n; i++)
		if (comp[i] == comp[nao(i)]) return 0;
	return 1;
}
