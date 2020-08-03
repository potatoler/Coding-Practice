#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=55;
int dis[maxn][maxn],n,m;
bool g[maxn][maxn][maxn];
int main(){
	memset(dis,0x3f,sizeof(dis));
	memset(g,false,sizeof(g));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		dis[u][v]=1;
		g[u][v][0]=true;
	}
	for(int k=1;k<=maxn;k++)
		for(int i=1;i<=n;i++)
			for(int t=1;t<=n;t++)
				for(int j=1;j<=n;j++)
					if(g[i][t][k-1]&&g[t][j][k-1]){
						g[i][j][k]=true;
						dis[i][j]=1;
					}
	for(int t=1;t<=n;t++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][t]+dis[t][j]);
	printf("%d",dis[1][n]);
	return 0;
}