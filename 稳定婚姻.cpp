#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#define int long long
using namespace std;
const int MaxN = 10004;
int n, m, cntEdge, head[MaxN], stack[MaxN], top, cntDFN, cntUnit;
map<string, int> couple;
struct Edge{
    int destinaiton, nextEdge;
}edge[MaxN * 4];
struct Vertex{
    int LOW, DFN, unit;
    bool visited;
}vertex[MaxN];

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
    edge[cntEdge].destinaiton = v;
    edge[cntEdge].nextEdge = head[u];
    head[u] = cntEdge;
}

inline void Tarjan(int x){
    vertex[x].DFN = vertex[x].LOW = ++cntDFN;
    stack[++top] = x;
    vertex[x].visited = true;
    for(int i = head[x]; i; i = edge[i].nextEdge){
        int des = edge[i].destinaiton;
        if(!vertex[des].DFN){
            Tarjan(des);
            vertex[x].LOW = min(vertex[x].LOW, vertex[des].LOW);
        }
        else if(vertex[des].visited) vertex[x].LOW = min(vertex[x].LOW, vertex[des].DFN);
    }
    if(vertex[x].DFN == vertex[x].LOW){
        ++cntUnit;
        int v;
        do{
            v = stack[top--];
            vertex[v].visited = false;
            vertex[v].unit = cntUnit;
        }while(x != v);
    }
    return;
}

signed main(){
    n = Read();
    string boy, girl;
    for(int i=1 ;i<=n; i++){
        cin>>girl>>boy;
        couple[girl] = i;
        couple[boy] = i+n;
        AddEdge(i, i+n);
    }
    m = Read();
    for(int i=1; i<=m; i++){
        cin>>girl>>boy;
        AddEdge(couple[boy], couple[girl]);
    }
    for(int i=1; i<=n*2; i++)
        if(!vertex[i].DFN) Tarjan(i);
	for(int i=1; i<=n; i++) {
		if(vertex[i].unit == vertex[i+n].unit) printf("Unsafe\n");
		else printf("Safe\n");
	}
	return 0;
}