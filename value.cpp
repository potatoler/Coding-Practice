#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int MaxN=5005, Inf=200005;
struct Item{
	int value, w;
}a[MaxN];
int n,tmp,ans,f[Inf],mx;

bool cmp(Item x, Item y){
	return x.w > y.w;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].value, &a[i].w);
		mx=max(mx,a[i].value);
	}
	sort(a+1,a+1+n,cmp);
	ans = 0;
	for(int i=1;i<=mx;i++) 
		f[i]=0;
	for(int j=1;j<=n;j++)
		f[j] = -Inf;
	for(int i=1;i<=n;i++)
		for(int j=n-1;j>=0;j--)
			if(f[j] != -Inf) f[j+1] = max(f[j+1], f[j]+a[i].value - a[i].w * j);
	for(int i=1;i<=mx;i++)
		ans = max(ans,f[i]);
	printf("%d",ans);
}