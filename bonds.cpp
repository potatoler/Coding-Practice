#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=10000005;
int s,n,d,f[maxn];
struct Bond{
	int w,v;
}b[maxn];
int main(){
	scanf("%d%d%d",&s,&n,&d);
	for(int i=1;i<=d;i++)
		scanf("%d%d",&b[i].w,&b[i].v);
	for(int k=1;k<=n;k++){
		for(int i=1;i<=d;i++)
			for(int j=b[i].w;j<=s;j++)
				f[j]=max(f[j],f[j-b[i].w]+b[i].v);
		s+=f[s];
	}
	printf("%d\n",s);
	return 0;
}