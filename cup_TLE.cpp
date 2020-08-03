//#8-10 TLE 70pts
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=100005;
int a[maxn*2],n,f[maxn*2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[n+i]);
	for(int i=1;i<=n;i++)
		a[n+1-i]=a[n+i],f[n+1-i]=f[n+i]=1;
	f[0]=0;
	int ans=0;
	for(int i=1;i<=n*2;i++){
		for(int j=1;j<=i;j++)
			if(a[j]<a[i]) f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}