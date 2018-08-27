//2-SAT
//
//Retorna true se eh possivel definir valores
//Retorna false caso contrario
//
//Em n coloca o numero de variaveis e m = 2*n
//grafo em g e o inverso em G
//para adicionar a clausula (x ou y) chama add(x, y)
//se x tem que ser verdadeiro chama add(x, x)
//nao(x) retorna x negado
//o kosaraju tem que colocar a quem pertence o vertice i em r
//
//Complexidade: O(|V| + |E|)


int nao(int x){
	return (x + n) % m;
}

void add(int x, int y){
	//nao x implica y
	g[nao(x)].push_back(y);
	G[y].push_back(nao(x));

	//nao y implica em x
	g[nao(y)].push_back(x);
	G[x].push_back(nao(y));
}

bool doisSAT(){
	kosaraju();
	int ok = 1;

	for(int i = 0; i < n; i++)
		if(r[i] == r[i+n])
			ok = 0;

	return ok;
}