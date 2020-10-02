// Kruskal
//
// Gera e retorna uma AGM e seu custo total a partir do vetor de arestas (edg)
// do grafo
//
// O(m log(m) + m a(m))

typedef tuple<int,int,int> t3;

vector<t3> edg; // {peso,[x,y]}

// DSU em O(a(n))
void dsu_build();
int find(int a);
void unite(int a, int b);

pair<ll,vector<t3>> kruskal(int n) {
	dsu_build(n);
	sort(edg.begin(), edg.end());
	
	ll cost = 0;
	vector<t3> mst;
	for(auto [w,x,y] : edg) if(find(x) != find(y)) {
		mst.push_back({w,x,y});
		cost += w;
		unite(x,y);
	}
	return {cost,mst};
}
