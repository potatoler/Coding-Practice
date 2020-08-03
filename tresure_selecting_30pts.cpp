//暴力拆解为0/1背包, TLE, 30pts QWQ;
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxw=40005;
int n,W,ans;
int v[maxw],w[maxw],m[maxw],f[maxw];
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&v[i],&w[i],&m[i]);
	memset(f,0xcf,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++)
		for(int k=1;k<=m[i];k++)
			for(int j=W;j>=w[i];j--)
				f[j]=max(f[j],f[j-w[i]]+v[i]);
	for(int i=0;i<=W;i++)
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}