// Kruskal
//
// Gera AGM a partir do vetor de arestas
//
// O(m log(n))

int n;
vector<pair<int, pair<int, int> > > ar; // vetor de arestas
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
			// aresta faz parte da AGM
		}
	}
}
