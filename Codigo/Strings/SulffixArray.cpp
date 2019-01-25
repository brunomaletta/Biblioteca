#include <bits/stdc++.h>
#define MAX 100007
#define ALPHA 256
 
using namespace std;
 
struct sa{
    int p[MAX], rank[MAX], cnt[MAX], pn[MAX], rankn[MAX], n;
    string s;
 
    sa(string _s) {
        memset(p, 0, sizeof p);
        memset(rank, 0, sizeof rank);
        memset(rankn, 0, sizeof rankn);
        memset(pn, 0, sizeof pn);
        memset(cnt, 0, sizeof cnt);
        s = _s;
        n = _s.size();
    }
 
    void build(){
        for(int i = 0; i < n; i++) cnt[s[i]]++;
 
        for(int i = 1; i < ALPHA; i++) cnt[i] += cnt[i-1];
        for(int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
 
        rank[p[0]] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++){
            if(s[p[i]] != s[p[i-1]]) ++classes;
            rank[p[i]] = classes-1;
        }
 
        for(int h = 0; (1<<h) < n; h++){
            for(int i = 0; i < n; i++){
                pn[i] = p[i]-(1<<h);
                if(pn[i] < 0) pn[i] += n;
            }
 
            memset(cnt, 0, classes * sizeof(int));
            for(int i = 0; i < n; i++) cnt[rank[pn[i]]]++;
 
            for(int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
 
            for(int i = n-1; i >= 0; i--) p[--cnt[rank[pn[i]]]] = pn[i];
 
            rankn[pn[0]] = 0;
            classes = 1;
            for(int i = 1; i < n; i++){
                int mid1 = (p[i] + (1<<h))%n;
                int mid2 = (p[i-1] + (1<<h))%n;
                if(rank[p[i]] != rank[p[i-1]] || rank[mid1] != rank[mid2]) classes++;
 
                rankn[p[i]] = classes-1;
            }
 
            memcpy(rank, rankn, sizeof rank);
        }
 
    }
};
 
int main(){
    string txt;
    cin >> txt;
    txt+="$";
 
    sa arr = sa(txt);
    arr.build();
    for(int i = 1; i < txt.size(); i++) cout << arr.p[i] << "\n";
    return 0;
}
