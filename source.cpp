#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn=2005;
int n,tot,a[maxn],ans;
int dis[maxn][maxn];
void floyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
void add(int u,int v){
	dis[u][v]=dis[v][u]=1;
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)
		dis[i][i]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	floyd();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i]<a[j])
				ans=max(ans,a[j]*dis[i][j]);
	printf("%d",ans);
	return 0;
}