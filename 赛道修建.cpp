#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
#define int long long
using namespace std;
const int MaxN = 50004;
int n, m, ans, mid, head[MaxN], cntEdge, f[MaxN], g[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
multiset<int> seto;
multiset<int>::iterator it;
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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void DFS(int u, int fa){
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		if(v == fa) continue;
		DFS(v, u);
		f[u] += f[v];
	}
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		if(v == fa) continue;
		seto.insert(g[v]+edge[i].value);
	}
	while(seto.size()){
		int cur = *seto.rbegin();
		if(cur >= mid){
			it = seto.find(cur);
			f[u]++;
			seto.erase(it);
		}
		else break;
	}
	while(seto.size()){
		int cur = *seto.begin();
		seto.erase(seto.begin());
		it = seto.lower_bound(mid-cur);
		if(it == seto.end()) g[u] = cur;
		else{
			f[u]++;
			seto.erase(it);
		}
	}
}

signed main(){
	n = Read(), m = Read();
	int l = INT_MAX, r = 0;
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w), AddEdge(v, u, w);
		l = min(l, w), r += w;
	}
	while(l <= r){
		mid = (l + r) >> 1;
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		DFS(1,0);
		if(f[1] >= m){
			ans = max(ans, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	printf("%lld", ans);
	return 0;
}