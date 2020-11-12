#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 5000006, MaxM = 3000006;
int n, m, head[MaxN], cntEdge, mx, mn;
int stack[MaxN];
struct Edge{
	int destiantion, nextEdge, value;
}edge[MaxM*2];
bool visited[MaxN][2];
int value[MaxN][2], point[MaxN];
queue<int> posQ, typeQ;
#define max(x,y) (x > y ? x : y);
#define min(x,y) (x < y ? x : y);

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
	edge[cntEdge].destiantion = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Solve(int x){
	visited[x][0] = true;
	posQ.push(x), typeQ.push(0);
	int top = 0;
	stack[++top] = x;
	while(posQ.size()){
		int pos = posQ.front(), type = typeQ.front();
		posQ.pop(), typeQ.pop();
		for(int i = head[pos]; i; i = edge[i].nextEdge){
			int des = edge[i].destiantion;
//			printf("%lld ", des);
			if(!visited[des][0] && !visited[des][1]) stack[++top] = des;
			if(visited[des][type^1]){
				if(value[des][type^1] != edge[i].value - value[pos][type]){
					printf("NIE");
					exit(0);
				}
			}
			else{
				visited[des][type^1] = true;
				value[des][type^1] = edge[i].value - value[pos][type];
				posQ.push(des), typeQ.push(type^1);
			}
		}
//		printf("\n");
	}
//	for(int i=1; i<=top; i++){
//		printf("%lld ", stack[i]);
//	}
//	printf("\n");
	int l = 0, r = point[x], sum1 = 0, sum2 = 0;
	for(int i=1; i<=top; i++){
		int cur = stack[i];
		if(visited[cur][0]){
			l = max(l, -value[cur][0]);
			r = min(r, point[cur] - value[cur][0]);
		}
		if(visited[cur][1]){
			l = max(l, value[cur][1] - point[cur]);
			r = min(r, value[cur][1]);
		}
		if(visited[cur][0] && visited[cur][1]){
			if((value[cur][1] - value[cur][0]) & 1){
				printf("NIE");
				exit(0);
			}
			l = max(l, (value[cur][1] - value[cur][0]) >> 1);
			r = min(r, (value[cur][1] - value[cur][0]) >> 1);
		}
	}
	if(l > r){
		printf("NIE");
		exit(0);
	}
	for(int i=1; i<=top; i++){
		int cur = stack[i];
		if(visited[cur][0]){
			sum1 += point[cur] - l - value[cur][0];
			sum2 += point[cur] - r - value[cur][0];
		}
		else{
			sum1 += point[cur] + l - value[cur][1];
			sum2 += point[cur] + r - value[cur][1];
		}
	}
	if(sum1 > sum2) swap(sum1, sum2);
	mn += sum1;
	mx += sum2;
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		point[i] = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	for(int i=1; i<=n; i++)
		if(!visited[i][0] && !visited[i][1]) Solve(i);
	printf("%lld %lld", mn, mx);
	return 0;
}