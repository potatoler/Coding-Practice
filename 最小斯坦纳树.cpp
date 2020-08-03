#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include <queue>
#define int long long
using namespace std;
const int MaxN=510;
int n, m, k, cntEdge, p[MaxN], head[MaxN], des[2*MaxN], visited[MaxN], nextEdge[2*MaxN], value[2*MaxN], dp[MaxN][4200];
priority_queue < pair<int,int> > q;

inline void AddEdge(int x, int y, int z){
	des[++cntEdge] = y;
	nextEdge[cntEdge] = head[x];
	value[cntEdge] = z;
	head[x] = cntEdge;
	return;
}

inline void Dijkstra(int s){
	memset(visited,0,sizeof(visited));
	while(!q.empty()){
		pair <int,int> a = q.top();
		q.pop();
		if(visited[a.second]) continue;
		visited[a.second] = 1;
		for (int i=head[a.second]; i; i=nextEdge[i]) {
			if (dp[des[i]][s] > dp[a.second][s] + value[i]) {
				dp[des[i]][s] = dp[a.second][s] + value[i];
				q.push(make_pair(-dp[des[i]][s], des[i]));
			}
		}
	}
	return;
}

signed main (){
	memset(dp,0x3f,sizeof(dp));
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i=1;i<=m;i++){
		int x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	for(int i=1;i<=k;i++){
		scanf("%lld", &p[i]);
		dp[p[i]][1<<(i-1)] = 0;
	}
	for(int s=1;s<(1<<k);s++){
		for(int i=1;i<=n;i++){
			for(int subs=s&(s-1); subs; subs=s&(subs-1))
				dp[i][s] = min(dp[i][s], dp[i][subs] + dp[i][s^subs]);
			if (dp[i][s] != 0x3f3f3f3f) q.push(make_pair(-dp[i][s],i));
		}
		Dijkstra(s);
	}
	printf("%lld\n",dp[p[1]][(1<<k)-1]);
	return 0;
}