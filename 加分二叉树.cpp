#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=35;
int n,val[maxn],f[maxn][maxn],root[maxn][maxn];
void print(int l,int r){
	if(l>r) return;
	if(l==r){
		printf("%d ",l);
		return;
	}
	printf("%d ",root[l][r]);
	print(l,root[l][r]-1);
	print(root[l][r]+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for(int i=1;i<=n;i++)
		f[i][i]=val[i],f[i][i-1]=1;
	for(int i=n;i;i--)
		for(int j=i+1;j<=n;j++)
			for(int k=i;k<=j;k++)
				if(f[i][j]<f[i][k-1]*f[k+1][j]+f[k][k]){
					f[i][j]=f[i][k-1]*f[k+1][j]+f[k][k];
					root[i][j]=k;
				}
	printf("%d\n",f[1][n]);
	print(1,n);
	return 0;
}