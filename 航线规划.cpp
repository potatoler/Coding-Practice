#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#include<stack>
using namespace std;
const int MaxN = 30004, MaxM = 100005;
int n, m, cntEdge, cntDFN, cntOp, head[MaxN], depth[MaxN], father[MaxN], subtreeSize[MaxN], heavySon[MaxN], chainTop[MaxN], DFN[MaxN], LOW[MaxN], x[MaxM], y[MaxM], add[MaxN*4], sum[MaxN*4];
bool visited[MaxM];
struct Edge{
	int destination, nextEdge;
}edge[MaxM*2];
struct Operation{
	int op, a, b;
}operation[MaxM];
map<pair<int,int>,bool> record;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

inline void AddEdge(int u, int v){
	edge[++cntEdge] = (Edge){v, head[u]};
	head[u] = cntEdge;
}

inline int FindFather(int x){
	return father[x] == x ? x : father[x] = FindFather(father[x]);
}

inline void DFS1(int u){
	subtreeSize[u] = 1;
	for(int i = head[u]; i; i = edge[i].nextEdge)
	{
		int v = edge[i].destination;
		if(v != father[u]){
			father[v] = u;
			depth[v] = depth[u] + 1;
			DFS1(v);
			subtreeSize[u] += subtreeSize[v];
			if(subtreeSize[v] > subtreeSize[heavySon[u]]) heavySon[u] = v;
		}
	}
}

inline void DFS2(int u, int top){
	chainTop[u] = top;
	DFN[u] = ++cntDFN;
	if(heavySon[u]) DFS2(heavySon[u], top);
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		if(v != heavySon[u]  &&  v != father[u])DFS2(v,v);
	}
	LOW[u] = cntDFN;
}

inline void Update(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

inline void PassTag(int rt, int m){
	if(~add[rt]){
		add[rt<<1] = add[rt<<1|1] = add[rt];
		sum[rt<<1] = add[rt] * (m - (m >> 1));
		sum[rt<<1|1] = add[rt] * (m >> 1);
		add[rt] = -1;
	}
}

inline void Build(int l,int r,int rt){
	add[rt] = -1;
	if(l == r){
		sum[rt] = 1;
		return;
	}
	int m = (l+r) >> 1;
	Build(l,m,rt<<1);
	Build(m+1,r,rt<<1|1);
	Update(rt);
}

inline void Change(int L,int R,int c,int l,int r,int rt){
	if(L <= l && r <= R){
		add[rt] = c;
		sum[rt] = c*(r-l+1);
		return;
	}
	PassTag(rt,r-l+1);
	int m = (l+r)>>1;
	if(L <= m)Change(L,R,c,l,m,rt<<1);
	if(m<R)Change(L,R,c,m+1,r,rt<<1|1);
	Update(rt);
}

inline int Query(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R)return sum[rt];
	PassTag(rt,r-l+1);
	int m = (l+r)>>1,ret = 0;
	if(L <= m)ret += Query(L,R,l,m,rt<<1);
	if(m<R)ret += Query(L,R,m+1,r,rt<<1|1);
	return ret;
}

signed main(){
	n = Read(),m = Read();
	for(int i = 1 ;i <= m; ++i)
		x[i] = Read(), y[i] = Read();
		
	while(true){
		int op = Read();
		if(!(~op))break;
		int a = Read(),b = Read();
		operation[++cntOp] = (Operation){op,a,b};
		if(!op) record[make_pair(a,b)] = record[make_pair(b,a)] = true;
	}
	
	for(int i = 1; i <= n; ++i)
		father[i] = i;
	for(int i = 1; i <= m; ++i){
		int u = FindFather(x[i]),v = FindFather(y[i]);
		if(!record[make_pair(x[i],y[i])] && father[u] != v){
			father[u] = v;
			AddEdge(x[i],y[i]);
			AddEdge(y[i],x[i]);
			visited[i] = true;
		}
	}
	memset(father, 0, sizeof(father));
	
	DFS1(1);
	DFS2(1,1);
	Build(1,n,1);
	
	for(int i = 1;i <= m;++i)
		if(!visited[i] && !record[make_pair(x[i],y[i])]){
			int a = x[i],b = y[i];
			while(chainTop[a] != chainTop[b]){
				if(depth[chainTop[a]] > depth[chainTop[b]])swap(a,b);
				Change(DFN[chainTop[b]],DFN[b],0,1,cntDFN,1);
				b = father[chainTop[b]];
			}
			if(depth[a] > depth[b])swap(a,b);
			Change(DFN[a]+1,DFN[b],0,1,cntDFN,1);
		}
		
	stack<int> q;
	for(int i = cntOp; i; --i){
		int ans = 0, op = operation[i].op, a = operation[i].a, b = operation[i].b;
		while(chainTop[a] != chainTop[b]){
			if(depth[chainTop[a]] > depth[chainTop[b]]) swap(a,b);
			if(op) ans += Query(DFN[chainTop[b]],DFN[b],1,cntDFN,1);
			else Change(DFN[chainTop[b]],DFN[b],0,1,cntDFN,1);
			b = father[chainTop[b]];
		}
		if(depth[a] > depth[b])swap(a,b);
		if(op) q.push(ans + Query(DFN[a]+1,DFN[b],1,cntDFN,1));
		else Change(DFN[a]+1,DFN[b],0,1,cntDFN,1);
	}
	
	while(!q.empty()){
		printf("%d\n",q.top());
		q.pop();
	}
	
	return 0;
}