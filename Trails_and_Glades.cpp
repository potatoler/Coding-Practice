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
const int MaxN = 1000006;
int n, m;
struct Edge{
    int destination, nextEdge;
}edge[MaxN * 2];
int degree[MaxN], head[MaxN], cntEdge;
bool visited[MaxN], flag, haveEdge[MaxN];

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
    degree[v]++;
    haveEdge[v] = true;
}

inline void DFS(int x){
    visited[x] = true;
    if(degree[x] & 1) flag = true;
    for(int i = head[x]; i; i = edge[i].nextEdge){
        int des = edge[i].destination;
        if(!visited[des]) DFS(des);
    }
    return;
}

signed main(){
    n = Read(), m = Read();
    if(!m){
        printf("0");
        return 0;
    }
    for(int i=1; i<=m; i++){
        int u = Read(), v = Read();
        AddEdge(u,v);
        AddEdge(v,u);
    }
    haveEdge[1] = true;
    int single=0, unit=0, ans=0;
    for(int i=1;i<=n;i++){
        if(haveEdge[i]){
            if(!visited[i]){
                flag = false;
                DFS(i);
                unit++;
                if(!flag) single++;
            }
            if(degree[i] & 1) ans++;
        }
    } 
    if(unit >= 2) printf("%lld\n", ans/2+single);
    else printf("%lld\n", ans/2);
    return 0;
}