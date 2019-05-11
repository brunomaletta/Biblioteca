// Algoritmo de tarjan
//
// Computa pontos de articulacao
// e pontes
//
// O(n+m)

int in[MAX];
int low[MAX];
int parent[MAX];
vector<int> g[MAX];

bool is_art[MAX];

void dfs_art(int v, int p, int &d){
	parent[v] = p;
	low[v] = in[v] = d++;
	is_art[v] = false;
	for (int j : g[v]){
		if (j == p) continue;
		if (in[j] == -1){
			dfs_art(j, v, d);

			if (low[j] >= in[v]) is_art[v] = true;
			//if (low[j] >  in[v]) this edge is a bridge

			low[v] = min(low[v], low[j]);
		}
		else low[v] = min(low[v], in[j]);
	}
	if (p == -1){
		is_art[v] = false;
		int k = 0;
		for (int j : g[v])
			k += (parent[j] == v);
		if (k > 1) is_art[v] = true;
	}
}
