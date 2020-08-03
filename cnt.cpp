#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2005;
int n,tot,to[maxn*maxn],nxt[maxn*maxn],head[maxn],cnt;
bool vis[maxn];
int rd(){
	char ch=getchar();
    int f=1;
    int ret=0;
    for(; !isdigit(ch); ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch); ret=(ret<<1)+(ret<<3)+ch-'0',ch=getchar());
    return ret*f;
}
void add(int x,int y){
	tot++;
	to[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int main(){
	n=rd();
	char tmp;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>tmp;
			if(tmp=='1') add(i,j);
		}
	queue<int> q;
	for(int i=1;i<=n;i++){
		cnt++;
		memset(vis,false,sizeof(vis));
		q.push(i);
		vis[i]=true;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			vis[u]=false;
			for(int j=head[u];j;j=nxt[j]){
				int v=to[j];
				if(!vis[v]){
					q.push(v);
					vis[v]=true;
					cnt++;
				}
			}
		}
	}
	printf("%d",cnt);
	return 0;
}