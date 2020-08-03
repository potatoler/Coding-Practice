#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=105,mod=1000007;
int n,m,a[maxn],f[maxn][maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=min(j,a[i]);k++)
				f[i][j]=(f[i][j]+f[i-1][j-k])%mod;
	printf("%d",f[n][m]);
	return 0;
}