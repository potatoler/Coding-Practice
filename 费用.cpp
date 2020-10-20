#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200005, INF = 1e18;
int n, m, q, serial[MaxN], lastTime[MaxN], cntPath, cntEdge, pre[MaxN], suc[MaxN], head[MaxN], disS[MaxN], disT[MaxN];
bool onPath[MaxN];
struct Original_Edge{
	int from, to, value;
}oEdge[MaxN*2];
struct Edge{
	int serial, destination, nextEdge, value;
}edge[MaxN*2];
struct Node{
	int pos, dist;
	inline bool operator < (const Node &a) const{
		return a.dist < dist;
	}
};
struct SegmentTree{
	int l, r, value;
}tree[MaxN*4];

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

inline void AddEdge(int x, int u, int v, int w){
	cntEdge++;
	edge[cntEdge].serial = x;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Dijkstra(int s, int dis[], int mode){
	priority_queue<Node> pq;
	for(int i=1; i<=n; i++)
		dis[i] = INF;
	dis[s] = 0;
	pq.push((Node){s,0});
	while(pq.size()){
		Node top = pq.top();
		pq.pop();
		int x = top.pos;
		if(top.dist > dis[x]) continue;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dis[y] > top.dist + edge[i].value){
				lastTime[y] = edge[i].serial;
				dis[y] = top.dist + edge[i].value;
				if(mode == 1 && !onPath[y]) pre[y] = pre[x];
				if(mode == 2 && !onPath[y]) suc[y] = suc[x];
				pq.push((Node){y, dis[y]});
			}
		}
	}
	return;
}

inline void Record(){
	onPath[1] = true;
	pre[1] = suc[1] = 0;
	int cur = 1;
	for(int i=1; cur != n; i++){
		int ID = lastTime[cur];
		serial[ID] = i;
		cntPath++;
		cur = oEdge[ID].from ^ oEdge[ID].to ^ cur;
		onPath[cur] = true;
		pre[cur] = suc[cur] = i;
	}
	return;
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	tree[x].value = INF;
	if(l == r) return;
	int mid = (l + r) >> 1;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	return;
}

inline void Update(int x, int ql, int qr, int w){
	if(ql > qr) return;
	if(ql <= tree[x].l && tree[x].r <= qr){
		tree[x].value = min(tree[x].value, w);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(ql <= mid) Update(x<<1, ql, qr, w);
	if(qr > mid) Update(x<<1|1, ql, qr, w);
	return;
}

inline int Query(int x, int w){
	if(tree[x].l == tree[x].r) return tree[x].value;
	int mid = (tree[x].l + tree[x].r) >> 1;
	int ans = tree[x].value;
	if(w <= mid) ans = min(ans, Query(x<<1, w));
	else ans = min(ans, Query(x<<1|1, w));
	return ans;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=m; i++){
		oEdge[i] = (Original_Edge){Read(), Read(), Read()};
		AddEdge(i, oEdge[i].from, oEdge[i].to, oEdge[i].value);
		AddEdge(i, oEdge[i].to, oEdge[i].from, oEdge[i].value);
		serial[i] = -1;
	}
	Dijkstra(n, disT, 0);
	Record();
	Dijkstra(1, disS, 1);
	Dijkstra(n, disT, 2);
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld\n", serial[i], lastTime[i]);
	Build(1, 1, cntPath);
	for(int i=1; i<=m; i++){
		if(serial[i] == -1){
			Update(1, pre[oEdge[i].from]+1, suc[oEdge[i].to], disS[oEdge[i].from] + oEdge[i].value + disT[oEdge[i].to]);
			Update(1, pre[oEdge[i].to]+1, suc[oEdge[i].from], disS[oEdge[i].to] + oEdge[i].value + disT[oEdge[i].from]);
		}
	}
//	for(int i=1; i<=n*4; i++)
//		printf("%lld\n", tree[i].value);
	while(q--){
		int ID = Read(), newValue = Read(), ans = disS[n];
		if(serial[ID] != -1){
			ans = disS[n] - oEdge[ID].value + newValue;
			if(newValue > oEdge[ID].value) ans = min(ans, Query(1, serial[ID]));
		}
		else{
			if(newValue < oEdge[ID].value){
				ans = min(ans, disS[oEdge[ID].from] + newValue + disT[oEdge[ID].to]);
				ans = min(ans, disS[oEdge[ID].to] + newValue + disT[oEdge[ID].from]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}