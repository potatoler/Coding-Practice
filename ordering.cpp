#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[105],f[105][10005],n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(j==a[i]) f[i][j]=f[i-1][j]+1;
			else if(j>a[i]) f[i][j]=f[i-1][j]+f[i-1][j-a[i]];
			else f[i][j]=f[i-1][j];
		}
	printf("%d",f[n][m]);
	return 0;
}