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
const int MaxN = 5003, MaxP = 10004;
int n, p, f[MaxN][MaxP];
int head[MaxN], cntEdge, DFN[MaxN] ,cntDFN, siz[MaxN], weight[MaxN], value[MaxN];
struct Edge{
    int destination, nextEdge;
}edge[MaxN*2];

inline int Read(){
    int num = 0, op = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-')  op = -1;
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

inline void DFS(int x, int fa){
    siz[x] = 1;
    for(int i = head[x]; i; i = edge[i].nextEdge){
        int y = edge[i].destination;
        if(y == fa) continue;
        DFS(y,x);
        siz[x] += siz[y];
    }
    DFN[++cntDFN] = x;
    return;
}

signed main(){
//    freopen("medicine.in", "r", stdin);
//    freopen("medicine.out", "w", stdout);
    n = Read(), p = Read();
    for(int i=1; i<=n; i++){
        int w = Read(), fa = Read(), v = Read();
        weight[i] = w;
        value[i] = v;
        if(i>1) AddEdge(i, fa), AddEdge(fa, i);
    }
    DFS(1, 0);
    for(int i=1; i<=n; i++){
        int x = DFN[i];
        for(int j=0; j<=p; j++){
            int lst = 0;
            if(j - weight[x] >= 0) lst = f[i-1][j-weight[x]] + value[x];
            f[i][j] = max(f[i-siz[x]][j], lst);
        }
    }
    printf("%lld\n", f[n][p]);
}