#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, m, cntEdge, cntSCC, cntDFN;
int DFN[MaxN], LOW[MaxN], head[MaxN], SCC[MaxN], stack[MaxN], top;
bool visited[MaxN], notgood;
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

inline int Translate(char *opt){
	int res = 0;
	int i = 1;
	while (opt[i] >= '0' && opt[i] <= '9') {
		res = res * 10 + opt[i] - '0';
		i++;
	}
	return res;
}

inline void AddEdge(int u, int v){
	edge[++cntEdge] = (Edge){v, head[u]};
	head[u] = cntEdge;
}

inline void Tarjan(int x){
	DFN[x] = LOW[x] = ++cntDFN;
	stack[++top] = x;
	visited[x] = true;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int des = edge[i].destination;
		if(!DFN[des]){
			Tarjan(des);
			LOW[x] = min(LOW[x], LOW[des]);
		}
		else if(visited[des]) LOW[x] = min(LOW[x], DFN[des]);
	}
	if(DFN[x] == LOW[x]){
		++cntSCC;
		int v;
		do{
			v = stack[top--];
			visited[v] = false;
			SCC[v] = cntSCC;
		}while(x != v);
	}
	return;
}

inline void Reset(){// Haruki, reset!
	for(int i=0; i<MaxN*2; i++)
		edge[i].destination = edge[i].nextEdge = 0;
	for(int i=0; i<MaxN; i++)
		DFN[i] = LOW[i] = head[i] = SCC[i] = stack[i] = visited[i] = 0;
	cntEdge = cntSCC = cntDFN = notgood = n = m = top = 0;
}

inline void Solve(){
	Reset();
	n = Read(), m = Read();
	for (int x = 1; x <= m; x++){
		char opt[5], opt2[5];
		scanf("%s%s", opt, opt2);
		int i = Translate(opt), j = Translate(opt2);
		if (opt[0] == 'm'){
			if(opt2[0] == 'm') AddEdge(i+n, j), AddEdge(j+n, i);
			else AddEdge(i+n, j+n), AddEdge(j, i);
		}
		else{
			if(opt2[0] == 'm') AddEdge(i, j), AddEdge(j + n, i + n);
			else AddEdge(i, j + n), AddEdge(j, i + n);
		}
	}
	for(int i=1; i<=2*n; i++)
		if(!DFN[i]) Tarjan(i);
	for(int i=1; i<=n; i++)
		if(SCC[i] == SCC[i+n]){
			notgood = true;
			break;
		}
	if(notgood) printf("BAD\n");
	else printf("GOOD\n");
	return;
}

signed main(){
	int T = Read();
	while(T--)
		Solve();
	return 0;
}