#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 5003;
int n, m, ans[MaxN], tmp[MaxN], edge[MaxN][2], cnt;
bool visited[MaxN], normalTree;
int deleted_u, deleted_v;
vector<int> graph[MaxN];

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

inline bool Compare(){
	for(int i=1; i<=n ;i++)
		if(ans[i] != tmp[i]) return ans[i] > tmp[i];
	return false;
}

inline bool Check(int u, int v){
	if((u==deleted_u && v==deleted_v) || (u==deleted_v && v==deleted_u)) return false;
	return true;
}

inline void DFS(int u, int fa){
	if(normalTree) ans[++cnt] = u;
	else tmp[++cnt] = u;
	visited[u] = true;
	for(int i=0; i<graph[u].size(); i++){
		int v = graph[u][i];
		if(normalTree && !visited[v]) DFS(v,u);
		else if(!normalTree && !visited[v] && Check(u,v)) DFS(v,u);
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m ;i++){
		int u = Read(), v = Read();
		graph[u].push_back(v);
		graph[v].push_back(u);
		edge[i][0] = u, edge[i][1] = v;
	}
	if(m == n-1){
		normalTree = true;
		memset(ans, 0x3f, sizeof(ans));
		memset(visited, false, sizeof(visited));
		cnt = 0;
		for(int i=1; i<=n; i++)
			sort(graph[i].begin(), graph[i].end());
		DFS(1,0);
		for(int i=1; i<=n; i++)
			printf("%lld ", ans[i]);
	}
	else{
		memset(ans, 0x3f, sizeof(ans));
		memset(visited, false, sizeof(visited));
		for(int i=1; i<=n; i++)
			sort(graph[i].begin(), graph[i].end());
		for(int i=1; i<=m; i++){
			memset(tmp, 0, sizeof(tmp));
			memset(visited, 0, sizeof(visited));
			cnt = 0;
			deleted_u = edge[i][0], deleted_v = edge[i][1];
			DFS(1,0);
			if(Compare() && cnt == n)
				memcpy(ans, tmp, sizeof(tmp));
		}
		for(int i=1; i<=n; i++)
			printf("%lld ", ans[i]);
	}
	return 0;
}