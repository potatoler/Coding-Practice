#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<utility>
//#define int long long
using namespace std;
const int max1=500+10;
const int max2=5000+10;
int n,m,s,t,cnt1,cnt2;
int fa[max1];
struct Edge
{
	int x,y;
	int z;
}edge[max2*2];
bool cmp(Edge a,Edge b)
{
	return a.z<b.z;
}
int gcd(int a,int b)
{
	int r;
	while(b)
	{
		r=a%b;
		a=b;
		b=r;
	}
	return a;
}
int father(int a)
{
	if(a==fa[a]) return a;
	fa[a]=father(fa[a]);
	return fa[a];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	    scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].z);
	cin>>s>>t;
	sort(edge+1,edge+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int j;
		for(j=1;j<=n;j++) fa[j]=j;
		for(j=i;j<=m;j++)
		{
			int aa=father(edge[j].x);
			int bb=father(edge[j].y);
			if(aa==bb) continue;
			fa[aa]=bb;
			if(father(s)==father(t)) break;
		}
		if((i==1)&&(father(s)!=father(t)))
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
		if(father(s)!=father(t)) break;
		if(cnt1*edge[i].z>=cnt2*edge[j].z) cnt1=edge[j].z,cnt2=edge[i].z;
	}
	int js=gcd(cnt1,cnt2);
	if(js==cnt1)
	   cout<<cnt2/js;
	else 
	   if(cnt2==js)
	      cout<<cnt1/js;
	   else
	       cout<<cnt1/js<<"/"<<cnt2/js;
	return 0;
}