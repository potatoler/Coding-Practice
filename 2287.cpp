#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 2020;
int n, m, f[MaxN], w[MaxN], c[MaxN][MaxN];
//f[i]: fill a backpack with a volume of i
//c[i][j]: i-th object missing then fill a backpack with a volume of j
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=m;j>=w[i];j--)
			f[j] += f[j-w[i]], f[j] %= 10;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=m;j++){
			if(j>=w[i]) c[i][j]=(f[j] - c[i][j-w[i]] + 10) % 10;
			else c[i][j] = f[j];
			printf("%d",c[i][j]);
		}    
		printf("\n");        
	}
	return 0;    
}