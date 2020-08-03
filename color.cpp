#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000005;
int n,to[maxn],nxt[maxn],head[maxn],cor[maxn];
int tot,ans;
void add(int u,int v){
	tot++;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
void nuri(int x){
	int c=cor[x];
	for(int i=head[x];i;i=nxt[i]){
		if(cor[to[i]]==0){
			if(c==1) cor[to[i]]=2,ans++,nuri(to[i]);
			if(c==2) cor[to[i]]=1,nuri(to[i]);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		add(i,tmp);
	}
	cor[1]=1;
	nuri(1);
	printf("%d",max(ans,n-ans));
	return 0;
}