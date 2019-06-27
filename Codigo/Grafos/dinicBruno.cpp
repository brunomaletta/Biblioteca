// Dinic (Bruno)
//
// O(n^2 m)
// Grafo bipartido -> O(sqrt(n)*m)

struct edge {
    int p, c, id; // para, capacidade, id
    edge(int p_, int c_, int id_) : p(p_), c(c_), id(id_) {}
};
 
vector<vector<edge> > g(MAX);
vector<int> lev;
 
void add(int a, int b, int c) { // de a pra b com cap. c
    g[a].pb(edge(b, c, g[b].size()));
    g[b].pb(edge(a, 0, g[a].size()-1));
}
 
bool bfs(int s, int t) {
    lev = vector<int>(g.size(), -1); lev[s] = 0;
    queue<int> q; q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (auto& i : g[u]) {
            if (lev[i.p] != -1 or !i.c) continue;
            lev[i.p] = lev[u] + 1;
            if (i.p == t) return 1;
            q.push(i.p);
        }
    }
    return 0;
}
 
int dfs(int v, int s, int f = INF){
    if (v == s) return f;
    int tem = f;
    for (auto& i : g[v]) {
        if (lev[i.p] != lev[v] + 1 or !i.c) continue;
        int foi = dfs(i.p, s, min(tem, i.c));
        tem -= foi, i.c -= foi, g[i.p][i.id].c += foi;
    }
    if (f == tem) lev[v] = -1;
    return f - tem;
}
 
int fluxo(int s, int t) {
    int f = 0;
    while (bfs(s, t)) f += dfs(s, t);
    return f;
}
