#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005,maxv=20005;
const long long mod=998244353;
int n;
long long maxh,ans;
long long h[maxn],f[maxn][maxv*2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&h[i]);
		maxh=max(maxh,h[i]);
	}
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++){
			f[i][h[i]-h[j]+maxh]=(f[i][h[i]-h[j]+maxh]+f[j][h[i]-h[j]+maxh]+1)%mod;
			ans=(ans+f[j][h[i]-h[j]+maxh]+1)%mod;
		}
	ans=(ans+n)%mod;
	printf("%lld",ans);
	return 0;
}