// BIT Persistente

#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll LINF = 0x3f3f3f3f3f3f3f3fll;

#define MAXN 100010
vector<pair<int,ll> > FT[MAXN];
int n;
void clear()
{
	for(int i=1;i<=n;i++)
	{
		FT[i].clear();
		FT[i].push_back({-1,0});
	}
}
void add(int i,int v,int time)
{
	for(;i<=n;i+=i&(-i))
	{
		ll last=FT[i].back().second;
		FT[i].push_back({time,last+v});
	}
}
ll get(int i,int time)
{
	ll ret=0;
	for(;i>0;i-=i&(-i))
	{
		int pos = upper_bound(FT[i].begin(),FT[i].end(),
					make_pair(time,LINF))-FT[i].begin()-1;
		ret+=FT[i][pos].second;
	}
	return ret;
}
ll getRange(int a,int b,int time)
{
	return get(b,time)-get(a-1,time);
}
