// LIS Rec. Resp.

#include<bits/stdc++.h>
using namespace std;
#define sc(a) scanf("%d", &a)

typedef long long int ll;
const int INF = 0x3f3f3f3f;

#define MAXN 100100
int aux[MAXN],endLis[MAXN];
//usar upper_bound se puder >=
vector<int> LisRec(vector<int> v){
	int n=v.size();
	int lis=0;
	for (int i = 0; i < n; i++){
		int it = lower_bound(aux, aux+lis, v[i]) - aux;
		endLis[i] = it+1;
		lis = max(lis, it+1);
		aux[it] = v[i];
	}
	vector<int> resp;
	int prev=INF;
	for(int i=n-1;i>=0;i--){
		if(endLis[i]==lis && v[i]<=prev){
			lis--;
			prev=v[i];
			resp.push_back(i);
		}
	}
	reverse(resp.begin(),resp.end());
	return resp;
}

int main()
{
	int n;
	sc(n);
	vector<int> v(n);
	for(int i=0;i<n;i++)
		sc(v[i]);
	cout<<LisRec(v).size()<<endl;
	return 0;
}
