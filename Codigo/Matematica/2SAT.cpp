// 2-SAT
//
// Retorna se eh possivel atribuir valores
// ans[i] fala se a variavel 'i' eh verdadeira
// Grafo tem que caber 2n vertices
// add(x, y) adiciona implicacao x -> y
// Para adicionar uma clausula (x ou y)
// chamar add(nao(x), y)
// Se x tem que ser verdadeiro, chamar add(nao(x), x)
//
// O(|V|+|E|)

vector<int> g[MAX];
int n, vis[MAX], comp[MAX];
stack<int> s;
int id[MAX], p;
vector<int> ord;
int ans[MAX];

int dfs(int k) {
	int lo = id[k] = p++;
	s.push(k);
	vis[k] = 2;
	for (int i = 0; i < g[k].size(); i++) {
		if (!vis[g[k][i]])
			lo = min(lo, dfs(g[k][i]));
		else if (vis[g[k][i]] == 2)
			lo = min(lo, id[g[k][i]]);
	}
	if (lo == id[k]) while (1) {
		int u = s.top();
		s.pop(); vis[u] = 1;
		comp[u] = k;
		ord.push_back(u);
		if (u == k) break;
	}
	return lo;
}

void tarjan() {
	memset(vis, 0, sizeof(vis));

	p = 0;
	for (int i = 0; i < 2*n; i++) if (!vis[i]) dfs(i);
}

int nao(int x){ return (x + n) % (2*n); }

// x -> y  =  !x ou y
void add(int x, int y){
	g[x].push_back(y);
	// contraposicao
	g[nao(y)].push_back(nao(x));
}

bool doisSAT(){
	tarjan();
	for (int i = 0; i < n; i++)
		if (comp[i] == comp[nao(i)]) return 0;


	memset(ans, -1, sizeof(ans));
	for(auto at: ord) {
		if (ans[at] != -1) continue;

		ans[at] = 1;
		ans[nao(at)] = 0;
	}
	return 1;
}
