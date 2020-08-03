#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=10005;
int f[maxn],k[maxn],m[maxn],v,n,c;
int main(){
	scanf("%d%d%d",&v,&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&m[i],&k[i]);
	for(int i=1;i<=n;i++)
		for(int j=c;j>=k[i];j--)
			f[j]=max(f[j],f[j-k[i]]+m[i]);
	for(int i=1;i<=c;i++)
		if(f[i]>=v){
			printf("%d",c-i);
			return 0;
		}
	printf("Impossible");
	return 0;
}