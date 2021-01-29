// Dijkstra
//
// encontra menor distancia de x
// para todos os vertices
// se ao final do algoritmo d[i] = INF,
// entao x nao alcanca i
//
// O(m log(n))

ll d[MAX];
vector<pair<int,int>> g[MAX]; // {vizinho, peso}

int n;
 
void dijkstra(int x) {
	for(int i=0; i < n; i++) d[i] = LINF;
	d[x] = 0;
	priority_queue<pair<ll,int>> pq;
	pq.push({0,x});
 
	while(pq.size()) {
		auto [ndist,u] = pq.top(); pq.pop();
		if(-ndist > d[u]) continue;
 
		for(auto [idx,w] : g[u]) if(d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.push({-d[idx], idx});
		}
	}
}
