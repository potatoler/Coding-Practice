#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, k, head[MaxN], cntEdge, f[MaxN], g[MaxN], sz[MaxN], s[MaxN];
int fir_mx[MaxN], sec_mx[MaxN], res, ans;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

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

inline void DFS1(int x, int fa){
	sz[x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS1(y, x);
		sz[x] += sz[y];
	}
	return;
}

inline void DFS2(int x, int fa, int limit){
	f[x] = g[x] = (s[x] >= limit);
	fir_mx[x] = sec_mx[x] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS2(y, x, limit);
		if(f[y] == sz[y]){
			f[x] += f[y];
			g[x] += g[y];
		}
		else if(s[y] >= limit){
			if(f[y] > fir_mx[x]){
				sec_mx[x] = fir_mx[x];
				fir_mx[x] = f[y];
			}
			else if(f[y] > sec_mx[x]) sec_mx[x] = f[y];
		}
	}
	f[x] += fir_mx[x];
	return;
}

inline void DFS3(int x, int fa, int cnt, int limit){
	int tmp = f[x];
	if(cnt + sz[x] == n){
		g[x] += cnt;
		f[x] += cnt;
	}
	else if(cnt > fir_mx[x]){
		sec_mx[x] = fir_mx[x];
		fir_mx[x] = cnt;
		f[x] += fir_mx[x] - sec_mx[x];
	}
	else if(cnt > sec_mx[x]) sec_mx[x] = cnt;
	if(s[x] >= limit) res = max(res, g[x] + fir_mx[x]);
	if(tmp == sz[x]) return;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		if(s[x] < limit){
			DFS3(y, x, 0, limit);
			continue;
		}
		if(f[y] == fir_mx[x]) DFS3(y, x, f[x]-fir_mx[x]+sec_mx[x], limit);
		else if(f[y] == sz[y]) DFS3(y, x, f[x]-f[y], limit);
		else DFS3(y, x, f[x], limit);
	}
	return;
}

inline bool Judge(int mid){
	res = 0;
	DFS2(1, 0, mid);
	DFS3(1, 0, 0, mid);
	return res >= k;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++)
		s[i] = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	DFS1(1, 0);
	int l = 0, r = 1000000;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(Judge(mid)){
			ans = mid;
			l = mid+1;
		}
		else r = mid-1;
	}
	printf("%lld", ans);
	return 0;
}