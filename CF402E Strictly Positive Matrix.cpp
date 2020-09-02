#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, head[MaxN * MaxN], cntEdge;
bool visited[MaxN][MaxN], inStack[MaxN], flag;
int DFN[MaxN], LOW[MaxN], cntDFN, num;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * MaxN * 2];
stack<int> s;
#define des edge[i].destination

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

inline void Tarjan(int x){
	DFN[x] = LOW[x] = ++cntDFN;
	inStack[x] = true, s.push(x);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(!DFN[des]){
			Tarjan(des);
			LOW[x] = min(LOW[x], LOW[des]);
		}
		else if(inStack[des]) LOW[x] = min(LOW[x], DFN[des]);
	}
	int tmp;
	if(LOW[x] == DFN[x]){
		num++;
		do{
			tmp = s.top();
			s.pop();
			inStack[tmp] = false;
		}while(x != tmp);
	}
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)	
		for(int j=1; j<=n; j++){
			int tmp = Read();
			if(tmp) visited[i][j] = true;
			else flag = false;
		}
	if(flag){
		printf("YES");
		return 0;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(visited[i][j]) AddEdge(i,j);
	for(int i=1; i<=n; i++)
		if(!DFN[i]) Tarjan(i);
	if(num == 1) printf("YES");
	else printf("NO");
	return 0;
}