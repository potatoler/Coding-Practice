#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxm=300005,maxn=3005;
int n,m,d,h[maxn];
struct Monster{
	int a,b,c;
}g[maxn];
bool cmp(Monster x,Monster y){
	return x.a+x.b>y.a+y.b;
}
int main(){
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=n;i++)
		scanf("%d",&g[i].a);
	for(int i=1;i<=n;i++)
		scanf("%d",&g[i].b);
	for(int i=1;i<=m;i++)
		scanf("%d",&h[i]);
	sort(g+1,g+1+n,cmp);
	g[1].c=g[1].a*g[1].b;
	int tmp=d;
	for(int i=2;i<=n;i++){
		g[i].a+=tmp,g[i].b+=tmp;
		tmp+=d;
		g[i].c=g[i].a*g[i].b;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",g[i].c);
	printf("\n");
	for(int i=1;i<=m;i++){
		int cnt=0;
		while(h[i]>g[cnt+1].c&&cnt<n){
			h[i]-=g[cnt+1].c;
			cnt++;
		}
		printf("%d ",cnt);
	}
	return 0;
}