/*
拓扑排序：
如果对有向无环图进行拓扑排序，那么最终得到的序列长度不为n
时间复杂度 O(n+m)
维护一个队列 q
1. 统计每个点的入度，并将入度为0的点入队
2. 在 q 为空之前：
	从 q 中取出一个点 u，遍历从 u 出发的所有边，in[v]--
	如果现在点 v 入度为0，将点 v 入队
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100005;
int n,m,cnt,in[maxn],a[maxn];
int head[maxn*2],to[maxn*2],nxt[maxn*2],tot;
void add(int u,int v){
	tot++;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
	in[v]++;
}
void tops(){
	priority_queue<int,vector<int>,greater<int> > q;
	for(int i=1;i<=n;i++)
		if(!in[i]) q.push(i);
	while(q.size()){
		int x=q.top();
		q.pop();
		a[++cnt]=x;
		for(int i=head[x];i;i=nxt[i]){
			int y=to[i];
			in[y]--;
			if(!in[y]) q.push(y);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	tops();
	if(cnt==n)
		for(int i=1;i<=cnt;i++)
			printf("%d ",a[i]);
	else printf("OMG.");
	return 0;
}