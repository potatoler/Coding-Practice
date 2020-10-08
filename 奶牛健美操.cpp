#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, s, cntEdge, head[MaxN], len[MaxN], path[MaxN], limit, cut;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination

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

inline void DFS(int x, int father){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		DFS(thisSon, x);
	}
	int cntPath = 0;
	len[x] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		path[++cntPath] = len[thisSon] + 1;
	}
	if(cntPath == 0) return;
	if(cntPath == 1){
		if(path[1] > limit){
			cut++;
			return;
		}
		len[x] = path[1];
		return;
	}
	sort(path+1, path+1+cntPath);
	for(int i=cntPath; i>=1; i--){
		if(path[i] + path[i-1] > limit) cut++;
		else{
			len[x] = path[i];
			return;
		}
	}
	return;
}

inline bool Judge(int x){
	cut = 0, limit = x;
	DFS(1,0);
	if(cut <= s) return true;
	return false;
}

signed main(){
	n = Read(), s = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	int l = 0, r = n;
	while(l < r){
		int mid = (l + r) >> 1;
		if(Judge(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld", r);
}