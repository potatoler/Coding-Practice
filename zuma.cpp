#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,a[505],f[505][505];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		f[i][i]=1;
		if(a[i]==a[i+1]) f[i][i+1]=1;
		else f[i][i+1]=2;
	}
	// for(int i=n-1;i;i--)
	// 	for(int j=i+1;j<=n;j++){
	// 		if(a[i]==a[j]) f[i][j]=min(f[i][j],f[i+1][j-1]);
	// 		else for(int k=i;k<j;k++)
	// 		f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
	// 	}
	for(int len=3;len<=n;len++)
		for(int s=1;s+len-1<=n;s++){
			int l=s,r=s+len-1;
			if(a[l]==a[r]) f[l][r]=f[l+1][r-1];
			for(int k=l;k<r;k++)
				f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
		}
	printf("%d",f[1][n]);
}