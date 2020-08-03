#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
#define int long long
const int MaxN = 1000010;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];
int head[MaxN], cntEdge, circle[MaxN], circleSize, father[MaxN], DFN[MaxN], cntDFN, treeDiameter[MaxN], diameter, sum[MaxN], n;
bool visited[MaxN];
//#define thisSon edge[i].destination
#define thisValue edge[i].value

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
}

inline void DFS(int x){//find circle
	DFN[x] = ++cntDFN;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int thisSon = edge[i].destination;
		if(thisSon == father[x]) continue;
		if(DFN[thisSon]){
			if(DFN[thisSon] < DFN[x]) continue;
			circle[++circleSize] = thisSon;
			for(1; thisSon != x; thisSon = father[thisSon]) circle[++circleSize] = father[thisSon];
		}
		else {
			father[thisSon] = x;
			DFS(thisSon);
		}
	}
}

inline void DP(int x){
	visited[x] = true;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int thisSon = edge[i].destination;
		if(visited[thisSon]) continue;
		DP(thisSon);
		diameter = max(diameter, treeDiameter[x] + treeDiameter[thisSon] + thisValue);
		treeDiameter[x] = max(treeDiameter[x], treeDiameter[thisSon] + thisValue);
	}
}

inline int Solve(int x){
	cntDFN = circleSize = 0;
	DFS(x);
//	for(int i=1;i<=circleSize;i++)
//		printf("%lld ",circle[i]);
//	printf("\n");
	int len1 = 0, len2 = 0;
	circle[0] = circle[circleSize];
	for(int i=1; i<=circleSize; i++)
		visited[circle[i]] = true;
	for(int i=1; i<=circleSize; i++){
		diameter = 0;
		DP(circle[i]);
		len1 = max(len1, diameter);
	}
	if(circleSize == 2){
		for(int i = head[circle[1]]; i; i = edge[i].nextEdge){
			int thisSon = edge[i].destination;
			if(thisSon == circle[2]) len2 = max(len2, treeDiameter[circle[1]] + treeDiameter[circle[2]] + thisValue);
		}
//		printf("%lld %lld\n", len1, len2);
		return max(len1, len2);
	}
	for(int i=1; i<=circleSize; i++){
		int circleValue;
		for(int j = head[circle[i]]; j; j = edge[j].nextEdge){
			if(edge[j].destination == circle[i-1]){
				circleValue = edge[j].value;
				break;
			}
		}
		sum[i] = sum[i-1] + circleValue;
	}
	for(int i=1;i<circleSize;i++)
		sum[circleSize+i] = sum[circleSize] + sum[i]; //copy the circle
	int head = 0, tail = 0, deque[MaxN];
	deque[0] = 0;
	for(int i=1; i<circleSize*2; i++){
		while(head <= tail && deque[head] <= i - circleSize) head++;
		len2 = max(len2, treeDiameter[circle[deque[head]%circleSize]] + treeDiameter[circle[i%circleSize]] + sum[i] - sum[deque[head]]);
		while(head <= tail && sum[deque[tail]] - treeDiameter[circle[deque[tail]%circleSize]] >= sum[i] - treeDiameter[circle[i%circleSize]]) tail--;
		deque[++tail] = i;
	}
//	printf("%lld %lld\n", len1, len2);
	return max(len1, len2);
}

signed main(){
	scanf("%lld", &n);
	for(int u=1, v, w; u<=n; u++){
		scanf("%lld%lld", &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	int ans = 0;
	for(int i=1;i<=n;i++)
		if(!visited[i]) ans += Solve(i);
//	for(int i=1;i<=n;i++)
//		printf("%lld ", treeDiameter[i]);
//	printf("\n");
//	for(int i=1;i<=cntEdge;i+=2)
//		printf("%lld %lld\n", edge[i].destination, edge[i].value);
	printf("%lld", ans);
	return 0;
}