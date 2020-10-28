#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005, MaxM = MaxN*2;
int n, m, s, t, head[MaxM*2], cntEdge, cnto, dist[MaxM*2];
struct Oedge{
	int x, y, z;
	bool operator < (const Oedge &b) const{
		return z < b.z;
	}
}oedge[MaxM*2], stack[MaxM*2];
struct Edge{
	int destination, nextEdge, length;
}edge[MaxM*2];
vector<int> to[MaxM*2], val[MaxM*2];
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;

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
	edge[cntEdge].length = w;
	head[u] = cntEdge;
	return;
}

inline void Dijsktra(){
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	q.push(make_pair(dist[s],s));
	while(q.size()){
		int dis = q.top().first, u = q.top().second;
		q.pop();
		if(dist[u] < dis) continue;
		int cnt = to[u].size();
		for(int i=0; i<cnt; i++){
			int v = to[u][i], w = val[u][i];
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				q.push(make_pair(dist[v],v));
			}
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		oedge[++cnto] = (Oedge){u,v,w};
		oedge[++cnto] = (Oedge){v,u,w};
		AddEdge(u, cnto, cnto-1);
		AddEdge(v, cnto-1, cnto);
	}
	for(int i=1; i<=n; i++){
		int top = 0;
		for(int j = head[i]; j; j = edge[j].nextEdge){
			stack[++top] = (Oedge){edge[j].destination, edge[j].length, oedge[edge[j].destination].z};
		}
		if(!top) continue;
		sort(stack+1, stack+1+top);
		for(int j=1; j<=top; j++){
			int x = stack[j].x, y = stack[j].y, z = stack[j].z;
			to[x].push_back(y), val[x].push_back(z);
			to[y].push_back(x), val[y].push_back(z);
		}
		for(int j=1; j<top; j++){
			int y = stack[j].y, z = stack[j].z;
			++j;
			int yy = stack[j].y, zz = stack[j].z;
			--j;
			to[y].push_back(yy), val[y].push_back(zz-z);
			to[yy].push_back(y), val[yy].push_back(0);
		}
	}
	s = cnto+1, t = s+1;
	for(int i=1; i<=cnto; i++){
		if(oedge[i].x == 1){
			to[s].push_back(i);
			val[s].push_back(oedge[i].z);
		}
		if(oedge[i].y == n){
			to[i].push_back(t);
			val[i].push_back(oedge[i].z);
		}
	}
	Dijsktra();
	printf("%lld", dist[t]);
	return 0;
}