#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005, MaxM = 1000006;
struct Edge{
    int destination, nextEdge;
}oriEdge[MaxM], newEdge[MaxM];
int n, m, mod, oriHead[MaxN], newHead[MaxN], DFN[MaxN], LOW[MaxN], unit[MaxN], unitSize[MaxN], cntOriEdge, cntNewEdge, cntDFN, cntUnit;
int vertex[MaxN], solution[MaxN], used[MaxN];
int queue[MaxN], top;
bool inQueue[MaxN];
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

inline void AddEdge(int u, int v, bool ori){
    if(ori){
        cntOriEdge++;
        oriEdge[cntOriEdge].destination = v;
        oriEdge[cntOriEdge].nextEdge = oriHead[u];
        oriHead[u] = cntOriEdge;
    }
    else{
        cntNewEdge++;
        newEdge[cntNewEdge].destination = v;
        newEdge[cntNewEdge].nextEdge = newHead[u];
        newHead[u] = cntNewEdge;
    }
    return;
}

inline void Tarjan(int x){
    DFN[x] = LOW[x] = ++cntDFN;
    queue[++top] = x;
    inQueue[x] = true;
    for(int i = oriHead[x]; i; i = oriEdge[i].nextEdge){
        int des = oriEdge[i].destination;
        if(!DFN[des]){
            Tarjan(des);
            LOW[x] = min(LOW[x], LOW[des]);
        }
        else if(inQueue[des]) LOW[x] = min(LOW[x], DFN[des]);
    }
    if(DFN[x] == LOW[x]){
        ++cntUnit;
        int v;
        do{
            v = queue[top--];
            inQueue[v] = false;
            unitSize[cntUnit]++;
            unit[v] = cntUnit;
        }while(x != v);
    }
    return;
}

signed main(){
    n = Read(), m = Read(), mod = Read();
    for(int i=1; i<=m; i++){
        int u = Read(), v = Read();
        AddEdge(u, v, true);
    }
    for(int i=1; i<=n; i++)
        if(!DFN[i]) Tarjan(i);
    for(int i=1; i<=n; i++){
        vertex[i] = unitSize[i];
        solution[i] = 1;
        for(int j = oriHead[i]; j; j = oriEdge[j].nextEdge){
            int des = oriEdge[j].destination;
            if(unit[i] == unit[des]) continue;
            AddEdge(unit[i], unit[des], false);
        }
    }

	for(int i = cntUnit; i>=1; i--){
        for(int j = newHead[i]; j; j = newEdge[j].nextEdge){
            int des = newEdge[j].destination;
            if(used[des] == i) continue;
            used[des] = i;
            if(vertex[des] < vertex[i] + unitSize[des]){
                vertex[des] = vertex[i] + unitSize[des];
                solution[des] = solution[i];
            }
            else if(vertex[des] == vertex[i] + unitSize[des]) solution[des] = (solution[des] + solution[i]) % mod;
        }
    }
	int ans=0,tmp=0;
	for(int i=1; i<=cntUnit; i++){
		if(vertex[i] > ans){
			ans = vertex[i];
			tmp = solution[i];
		}else if(vertex[i] == ans) tmp = (solution[i] + tmp) % mod;
	}
	printf("%lld\n%lld", ans, tmp);
    return 0;
}