#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int T, n, k, ans, head[MaxN], cntEdge, serial[MaxN], cntDFN;
struct Edge{
	int destiantion, nextEdge;
}edge[MaxN * 2];
bool visited[MaxN];
#define thisSon edge[i].destiantion

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
	edge[cntEdge].destiantion = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int x, int father){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		DFS(thisSon, x);
	}
	serial[++cntDFN] = x;
}


inline void Reset(){
	// Haruki, reset!
	// Reset.
	memset(head, 0, sizeof(head));
	memset(visited, false, sizeof(visited));
	cntEdge = cntDFN = ans = 0;
	return;
}

signed main(){
	// freopen("tree.in", "r", stdin);
	// freopen("tree.out", "w", stdout);
	T = Read();
	while(T--){
		Reset();
		n = Read(), k = Read();
		for(int i=1; i<n; i++){
			int tmp = Read();
			AddEdge(i+1, tmp), AddEdge(tmp, i+1);
		}
		DFS(1,0);
		for(int i=1; i<=n; i++){
			if(k<=1) break;
			int x = serial[i];
			if(visited[x]) continue;
			for(int j = head[x]; j; j = edge[j].nextEdge){
				int y = edge[j].destiantion;
				if(!visited[y]){
					visited[y] = true;
					k -= 2;
					ans++;
					break;
				}
			}
			visited[x] = true;
		}
		ans += k;
		printf("%lld\n", ans);
	}
	return 0;
}