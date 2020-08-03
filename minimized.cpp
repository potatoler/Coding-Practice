#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=20005;
bool edge[maxn][maxn];
int mx[maxn];
int n,ans,T;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(edge,false,sizeof(edge));
		memset(mx,0,sizeof(mx));
		ans=0,n=0;
		scanf("%d",&n);
		for(int i=1;i<n;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			ans+=w;
			mx[u]=max(mx[u],w),mx[v]=max(mx[u],w);
			edge[u][v]=true,edge[v][u]=true;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(edge[i][j]==false&&i!=j){
					ans+=max(mx[i],mx[j])+1;
					edge[i][j]=true,edge[j][i]=true;
				}
		printf("%d\n",ans);
	}
	return 0;
}