#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=300;
int n,f[maxn][maxn],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i][i]);
		ans=max(ans,f[i][i]);
	}
	for(int i=n-1;i;i--)
		for(int j=i+1;j<=n;j++){
			for(int k=i;k<j;k++)
				if(f[i][k]==f[k+1][j]) f[i][j]=max(f[i][j],f[i][k]+1);
			ans=max(ans,f[i][j]);
		}
	printf("%d\n",ans);
	return 0;
}