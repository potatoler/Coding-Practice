#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int n, k, s[MaxN], head[MaxN], cntEdge, cnt[MaxN], sum[MaxN], ans;
struct Record{
	int u, v, c;
}record[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int depth, father, subtreeSize, heavySon, chainTop, serial;
	int arrive, leave;
}vertex[MaxN];
#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

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
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	return;
}

inline void DFS2(int x, int top){
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline void DFS3(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		DFS3(thisSon);
//		vertex[x].tag += vertex[thisSon].tag;
		vertex[x].arrive += vertex[thisSon].arrive;
		vertex[x].leave += vertex[thisSon].leave;
	}
//	cnt[vertex[x].serial] = vertex[x].tag;
	if(record[vertex[x].serial].c == 2) ans = (ans + sum[vertex[x].arrive]) % Mod;
	else if(record[vertex[x].serial].c == 1) ans = (ans + sum[vertex[x].leave]) % Mod;
	return;
}

signed main(){
//	freopen("walk.in", "r", stdin);
//	freopen("walk.out", "w", stdout);
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), c = Read();
		record[i] = {u,v,c};
		AddEdge(u,v), AddEdge(v,u);
	}
	DFS1(1);
	DFS2(1,0);
	for(int i=1; i<n; i++){
		if(vertex[record[i].u].depth > vertex[record[i].v].depth){
			if(record[i].c == 1) record[i].c = 2; // calculate when leave
			vertex[record[i].u].serial = i;
		}
		else{
			if(record[i].c == 1) record[i].c = 1; // calculate when arrive
			vertex[record[i].v].serial = i;
		}
	}
	k = Read();
	s[1] = Read();
	for(int i=2; i<=k; i++){
		s[i] = Read();
		int lca = LCA(s[i],s[i-1]);
		vertex[s[i-1]].leave++;
		vertex[lca].leave--;
		vertex[s[i]].arrive++;
		vertex[lca].arrive--;
	}
//	k = Read();
//	for(int i=1; i<=k; i++){
//		int u = Read(), v = Read();
//		vertex[u].tag++;
//		vertex[v].tag++;
//		vertex[LCA(u,v)].tag -= 2;
//	}
	int tmp = 1;
	for(int i=1; i<=n; i++){
		sum[i] = (sum[i-1] + tmp) % Mod;
		tmp = (tmp * 2) % Mod;
	}
	DFS3(1);
//	for(int i=1; i<n; i++){
//		switch(record[i].c){
//			case 0:{
//				cnt[i] = 0;
//				break;
//			}
//			case 1:{
//				cnt[i] = (cnt[i] + 1) / 2;
//				break;
//			}
//			case 2:{
//				cnt[i] = cnt[i] / 2;
//				break;
//			}
//		}
//		ans = (ans + sum[cnt[i]]) % Mod;
//	}
	printf("%lld", ans);
//	for(int i=1; i<n; i++)
//		printf("%lld ", vertex[i].arrive + vertex[i].leave);
	return 0;
}