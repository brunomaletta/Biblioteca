// Steiner Tree
//
// encontra a arvore de menor peso que cobre os vertices S e retorna o peso e a solução
// descomenta os vw's e coloca dentro dos parenteses para ter peso nos vertices
//
// k = |S|
//  O(3^k * n + 2^k * m log m)

vector<pair<int, long long>> g[MAX]; // {vizinho, peso}
long long d[1 << K][MAX]; //[2^k][n]
//int vw[MAX];
int n;

pair<ll,vector<pair<int,int>>> steiner(const vector<int> &S){
    int k = S.size();k--;
    for(int mask = 0; mask < (1 << k); mask++)for(int v = 0; v < n; v++) d[mask][v] = LINF;
    for(int i = 0; i < k; ++i) {
        d[1 << i][S[i]] = 0 /*+ vw[S[i]]*/;
    }
    for(int mask = 1; mask < (1 << k); ++mask) {
        for(int a = mask, b = 0; b > a; a = (a-1) & mask, b = mask ^ a){//itera sobre as particoes
            for(int v = 0; v < n; ++v) {
                d[mask][v] = min(d[mask][v], d[a][v] + d[b][v] );//- vw[v]
            }
        }
        priority_queue<pair<ll, int>> pq;
        for(int v = 0; v < n; ++v) {
            if(d[mask][v] == LINF) continue;
            pq.emplace(-d[mask][v], v);
        }
        while (pq.size()) {
            auto [ndist, u] = pq.top(); pq.pop();
            if (-ndist > d[mask][u]) continue;
            for (auto [idx, w] : g[u]) if (d[mask][idx] > d[mask][u] + w ) {//+ vw[idx]
                d[mask][idx] = d[mask][u] + w /*+ vw[idx]*/;
                pq.emplace(-d[mask][idx], idx);
            }
        }
    }
    vector<pair<int,int>> edges;
    queue<pair<int, int>> q;
    ll ans = d[(1 << k) - 1][S[k]];
    q.emplace((1<<k)-1,S[k]);
    while(q.size()){
        bool cont = 0;
        auto [mask,u] = q.front();q.pop();
        if(!mask)continue;
        for (auto [idx, w] : g[u]){
            if(d[mask][u] == d[mask][u] + w ){//- vw[u]
                cont = 1;
                edges.emplace_back(u,idx);
                q.emplace(mask,idx);
                break;
            }
        }
        if(cont)continue;
        for(int a = mask, b = 0; b > a; a = (a-1) & mask, b = mask ^ a){
            if(d[mask][u] == d[a][u] + d[b][u] ){//-vw[u]
                q.push_back(a,u);
                q.push_back(b,u);
                break;
            }
        }
    }
    return {ans,edges};
}
