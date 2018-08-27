// Kruskal
//
// Gera AGM a partir do vetor de arestas
//
// O(m log(m))

int n;
vector<pair<int, pair<int, int> > > ar; // vetor de arestas
vector<int> agm;                        // agm[i] eh 1 sse a i-esima aresta ta na AGM
int v[MAX];

// Union-Find em O(log(n))
void build();
int find(int k);
void une(int a, int b);

void kruskal() {
	build();

	sort(ar.begin(), ar.end());
	for (int i = 0; i < (int) ar.size(); i++) {
		int a = ar[i].s.f, b = ar[i].s.s;
		if (find(a) != find(b)) {
			une(a, b);
			agm.pb(1);
		} else agm.pb(0);
	}
}
