// Matroid
//
// Matroids de Grafo e Particao
// De modo geral, toda Matroid contem um build() linear
// e uma funcao constante oracle()
// oracle(i) responde se o conjunto continua independente 
// apos adicao do elemento i
// oracle(i, j) responde se o conjunto continua indepente
// apos trocar o elemento i pelo elemento j
//
// Intersecao sem peso O(n^2*r)
// em que n eh o tamanho do conjunto e r eh o tamanho da resposta

// Matroid Grafica
// Matroid das florestas de um grafo
// Um conjunto de arestas eh independente se formam uma floresta
//
// build() : O(n)
// oracle() : O(1)
// 0ea2fe

struct GraphicMatroid {
    int n, m;
    vector<array<int, 2>> edges;
    vector<vector<int>> g;
    vector<int> comp, in, out;
    GraphicMatroid(int n_, vector<array<int, 2>>& edges_) : n(n_), m(edges_.size()), edges(edges_), g(n), comp(n), in(n), out(n) {}
    int t = 0;
    void dfs(int u) {
        in[u] = t++;
        for (auto v : g[u]) {
            if (in[v] != -1) continue;
            comp[v] = comp[u];
            dfs(v);
        }
        out[u] = t;
    }
    void build(vector<int>& I) {
        t = 0;
        for (int u = 0; u < n; ++u) {
            g[u].clear(), in[u] = -1;
        }
        for (auto e : I) {
            auto [u, v] = edges[e];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int u = 0; u < n; ++u) {
            if (in[u] != -1) continue;
            comp[u] = u;
            dfs(u);
        }
    }
    bool is_ancestor(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    bool oracle(int e) {
        return comp[edges[e][0]] != comp[edges[e][1]];
    }
    bool oracle(int e, int f) {
        if (oracle(f)) return true;
        int u = edges[e][in[edges[e][0]] < in[edges[e][1]]];
        return is_ancestor(u, edges[f][0]) != is_ancestor(u, edges[f][1]);
    }
};


// Matroid de particao ou cores
// Um conjunto eh independente se a quantidade de elementos
// de cada cor nao excede a capacidade da cor
// Quando todas as capacidades sao 1, um conjunto eh independente
// se todas as suas cores sao distintas
// 
// build() : O(n)
// oracle() : O(1)
// 1e4fe7

struct PartitionMatroid {
    vector<int> cap, color, d;
    PartitionMatroid(vector<int>& cap_, vector<int>& color_) : cap(cap_), color(color_), d(cap.size()) {}
    void build(vector<int>& I) {
        fill(d.begin(), d.end(), 0);
        for (auto u : I) d[color[u]]++;
    }
    bool oracle(int u) {
        return d[color[u]] < cap[color[u]];
    }
    bool oracle(int u, int v) {
        return color[u] == color[v] || oracle(v);
    }
};


// Intersecao de matroid sem pesos
// Dadas duas matroids M1 e M2 definidas sobre o mesmo
// conjunto I, retorna o maior subconjunto de I
// que eh independente tanto para M1 quanto para M2
//
// O(n^2*r)
// fad211

// Matroid "pesada" deve ser a M2
template<typename Matroid1, typename Matroid2>
vector<int> matroid_intersection(int n, Matroid1& M1, Matroid2& M2) {
    vector<bool> b(n);
    vector<int> I[2];
    while (true) {
        for (int t : {0, 1}) I[t].clear();
        for (int u = 0; u < n; ++u) I[b[u]].push_back(u);
        
        M1.build(I[1]), M2.build(I[1]);
        vector<bool> target(n), pushed(n);
        queue<int> q;
        for (auto u : I[0]) {
            target[u] = M2.oracle(u);
            if (M1.oracle(u)) {
                pushed[u] = true;
                q.push(u);
            }
        }
        vector<int> p(n, -1);
        bool converged = true;
        while (not q.empty()) {
            int u = q.front();
            q.pop();
            if (target[u]) {
                converged = false;
                for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
                break;
            }
            for (auto v : I[!b[u]]) {
                if (pushed[v]) continue;
                if ((b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u))) {
                    p[v] = u;
                    pushed[v] = true;
                    q.push(v);
                }
            }
        }
        if (converged) break;
    }
    return I[1];
}
