#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
#define fake false
using namespace std;
const int MaxN = 1000006*2;
int n, cntEdge, head[MaxN], match[MaxN], visited[MaxN], stamp;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];

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

inline bool Find(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(visited[y] ^ stamp){
			visited[y] = stamp;
			if(!match[y] || Find(match[y])){
				match[y] = x;
				return !fake;
			}
		}
	}
	return fake;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		int a = Read(), b = Read();
		AddEdge(a, i), AddEdge(b, i);
	}
	for(int i=1; i<=10001; i++){
		stamp++;
		if(!Find(i)){
			printf("%lld", i-1);
			break;
		}
	}
	return 0;
}