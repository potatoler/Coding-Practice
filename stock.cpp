#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5005;
int n,f[maxn],a[maxn],ans,res,len[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<=i;j++)
			if(a[i]<a[j]) f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	for(int i=1;i<=n;i++){
		if(f[i]==1) len[i]=1;
		for(int j=1;j<i;j++){
			if(a[i]<a[j]&&f[i]==f[j]+1) len[i]+=len[j];
			if(a[i]==a[j]&&f[i]==f[j]) len[i]-=len[j];
		}
	}
	for(int i=1;i<=n;i++)
		if(ans==f[i]) res+=len[i];
	printf("%d %d",ans,res);
	return 0;
}