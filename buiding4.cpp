#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000005;
long long a[maxn],b[maxn],c[maxn];
char o[maxn];
int n,cnta,cntb;
void dfs(int x){
	if(x==n*2+1){
		for(int i=1;i<=n*2;i++)
			printf("%c",o[i]);
		exit(0);
	}
	if(a[x]>c[x-1]&&cnta<n){
		c[x]=a[x],o[x]='A';
		cnta++;
		dfs(x+1);
		cnta--;
		c[x]=0,o[x]=0;
	}
	if(b[x]>c[x-1]&&cntb<n){
		c[x]=b[x],o[x]='B';
		cntb++;
		dfs(x+1);
		cntb--;
		c[x]=0,o[x]=0;
	}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n*2;i++)
		scanf("%lld",&b[i]);
	// for(int i=1;i<=n*2;i++)
	// 	o[i]='A',c[i]=a[i];
	dfs(1);
	printf("-1");
	return 0;
}