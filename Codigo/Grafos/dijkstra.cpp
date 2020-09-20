// Dijkstra
//
// encontra menor distancia de x
// para todos os vertices
// se ao final do algoritmo d[i] = INF,
// entao x nao alcanca i
//
// O(m log(n))

int d[MAX];
vector<vector<pair<int,int>>> g(MAX); // {vizinho, custo}

int n;
 
void dijkstra(int x) {
	for(int i=0; i < n; i++) d[i] = INF;
	d[x] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push({0,x});
 
	while(pq.size()) {
		auto [dist,u] = pq.top(); pq.pop();
		if(-dist > d[u]) continue;
 
		for(auto p : g[u]) if(d[p.f] > d[u] + p.s) {
			d[p.f] = d[u] + p.s;
			pq.push({-d[p.f], p.f});
		}
	}
}
