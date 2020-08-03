#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1005;
int n,m,ans,vis[1005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		vis[u]++,vis[v]++;
	}
	for(int i=1;i<=n;i++)
		if(vis[i]%2==1) ans++;
	printf("%d\n",ans/2);
	return 0;
}