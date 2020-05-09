#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=3005;
int a[maxn],b[maxn],n,f[maxn][maxn],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j];
			if(a[i]==b[j]){
				int len=1;
				for(int k=1;k<j;k++)
					if(a[i]>b[i])
						len=max(len,f[i-1][k]+1);
				f[i][j]=max(f[i][j],len);
			}
		}
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,f[n][i]);
	printf("%d\n",ans);
}