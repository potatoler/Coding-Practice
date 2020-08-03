#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
char s[55];
int f[55][55];
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
		f[i][i]=1;
	for(int i=n-1;i;i--)
		for(int j=i+1;j<=n;j++){
			if(s[i]==s[j]) f[i][j]=min(f[i+1][j],f[i][j-1]);
			else for(int k=i;k<j;k++)
			f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	printf("%d",f[1][n]);
	return 0;
}