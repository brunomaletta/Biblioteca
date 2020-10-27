// Baby step Giant step
// 
// Resolve Logaritmo Discreto a^x = b mod m, m primo em O(sqrt(n)*hash(n))
// Meet In The Middle, decompondo x = i * ceil(sqrt(n)) -j, i,j<=ceil(sqrt(n))

int babyStep(int a,int b,int m)
{
	unordered_map<int,int> mapp;
	int sq=sqrt(m)+1;
	ll asq=1;
	for(int i=0; i<sq; i++)
		asq=(asq*a)%m;
	ll curr=asq;
	for(int i=1; i<=sq; i++)
	{
		if(!mapp.count(curr))
			mapp[curr]=i;
		curr=(curr*asq)%m;
	}
	int ret=INF;
	curr=b;
	for(int j=0; j<=sq; j++)
	{
		if(mapp.count(curr))
			ret=min(ret,(int)(mapp[curr]*sq-j));
		curr=(curr*a)%m;
	}
	if(ret<INF) return ret;
	return -1;
}
int main()
{
	int a,b,m;
	while(cin>>a>>b>>m,a or b or m)
	{
		int x=babyStep(a,m,b);
		if(x!=-1)
			cout<<x<<endl;
		else
			cout<<"No Solution"<<endl;
	}
	return 0;
}
