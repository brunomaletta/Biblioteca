#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define inf 1e9

struct edge{
	int p, c, id; //para, capacidade, id
	edge() {p = c = id = 0;}
	edge(int p, int c, int id):p(p), c(c), id(id){}
};

vector<vector<edge> > g; //define o tamanho depois
vector <int> lev;

void add(int a, int b, int c){
	//de a para b com capacidade c
	edge d = {b, c, (int) g[b].size()};
	edge e = {a, 0, (int) g[a].size()};
	g[a].pb(d);
	g[b].pb(e);
}

bool bfs(int s, int t){
	//bfs de s para t construindo o level
	for(int i = 0; i < g.size(); i++)
		lev[i] = -1;
	lev[s] = 0;

	queue <int> q;
	q.push(s);
	while(q.size()){
		int u = q.front(); q.pop();

		for(int i = 0; i < g[u].size(); i++){
			edge e = g[u][i];
			if(lev[e.p] != -1 || !e.c)
				continue;
			lev[e.p] = lev[u] + 1;
			if(e.p == t)
				return true;
			q.push(e.p);
		}
	}

	return false;
}

int dfs(int v, int s, int f){
	if(v == s || !f)
		return f;

	int flu = f;
	for(int i = 0; i < g[v].size(); i++){
		edge e = g[v][i]; int u = e.p;

		if(lev[u] != lev[v] + 1 || !e.c)
			continue;

		int tenta = dfs(u, s, min(flu, e.c));
		if(tenta){
			flu -= tenta;
			g[v][i].c -= tenta;
			g[u][e.id].c += tenta;
		}
	}

	if(flu == f)
		lev[v] = -1;
	return f - flu;
}

int fluxo(int s, int t){
	int r = 0;
	while(bfs(s, t))
		r += dfs(s, t, inf);
	return r;
}

//ja tem ate o debug
void imprime(){
	for(int i = 0; i < g.size(); i++){
		printf("%i -> ", i);
		for(int j = 0; j < g[i].size(); j++)
			printf("(%i %i)", g[i][j].p, g[i][j].c);
		printf("\n");
	}
	printf("\n");
}