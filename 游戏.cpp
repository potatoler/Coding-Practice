#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, d, m, DFN[MaxN], LOW[MaxN], SCC[MaxN], cntEdge, cntDFN, cntSCC, x[MaxN], y[MaxN], pos[MaxN], cntX;
int destination[MaxN*2], nextEdge[MaxN*2], head[MaxN], stack[MaxN], top;
bool visited[MaxN];
char ans[MaxN], map[MaxN], p1[MaxN], p2[MaxN];
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
	destination[cntEdge] = v;
	nextEdge[cntEdge] = head[u];
	head[u] = cntEdge;
	return;
}

inline void Tarjan(int cur){
	DFN[cur] = LOW[cur] = ++cntDFN;
	visited[cur] = true;
	stack[++top] = cur;
	for(int i = head[cur]; i; i = nextEdge[i]){
		int des = destination[i];
		if(!DFN[des]){
			Tarjan(des);
			LOW[cur] = min(LOW[cur], LOW[des]);
		}
		else if(visited[des]) LOW[cur] = min(LOW[cur], DFN[des]);
	}
	if(LOW[cur] == DFN[cur]){
		++cntSCC;
		int v;
		while(top){
			SCC[stack[top]] = cntSCC;
			visited[stack[top]] = false;
			if(stack[top--] == cur) break;
		}
	}
	return;
}

inline bool Check(){
	for(int i=1; i<=n*2; i++)
		if(!DFN[i]) Tarjan(i);
//	for(int i=1;i<=n*2;i++)
//		printf("%lld ",LOW[i]);
	for(int i=1; i<=n; i++){
		if(SCC[i] == SCC[i+n]) return false;
		if(SCC[i] < SCC[i+n]) ans[i] = (map[i] == 'A')? 'B':'A';
		else ans[i] = (map[i] == 'C')? 'B':'C';
	}
	for(int i=1; i<=n; i++)
		printf("%c",ans[i]);
	return true;
}

inline void Reset(){
	#define clear(a) memset(a, 0, sizeof(a))
	clear(head), clear(DFN), clear(LOW), clear(visited), clear(SCC), clear(stack), clear(nextEdge);
	cntEdge = cntDFN = cntSCC = top = 0;
}

signed main(){
	n = Read(), d = Read();
	scanf("%s", map+1);
	m = Read();
	for(int i=1; i<=m; i++)
		scanf("%lld %c %lld %c", &x[i], &p1[i], &y[i], &p2[i]);
	for(int i=1; i<=n; i++)
		if((map[i] -= 32) && map[i] == 'X') pos[++cntX] = i;
//	Solve();
	for(int i=0; i<(1<<d); i++){
		Reset();
		for(int j=1; j<=d; j++)
			map[pos[j]] = (i & (1<<(j-1)))? 'A':'B';
		for(int j=1; j<=m; j++){
			if(p1[j] == map[x[j]]) continue;
			if(p2[j] == map[y[j]]){
				if(p1[j] == 'C' || (p1[j] == 'B' && map[x[j]] == 'C')) AddEdge(x[j]+n, x[j]);
				else AddEdge(x[j], x[j]+n);
				continue;
			}
			int add1 , add2;
			if(p1[j] == 'C' || (p1[j] == 'B' && map[x[j]] == 'C')) add1 = n;
			else add1 = 0;
			if(p2[j] == 'C' || (p2[j] == 'B' && map[y[j]] == 'C')) add2 = n;
			else add2 = 0;
			AddEdge(x[j] + add1, y[j] + add2);
			AddEdge(y[j] - add2 + n, x[j] - add1 + n);
		}
		if(Check()) return 0;
	}
	printf("-1");
	return 0;
}