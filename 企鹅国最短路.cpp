#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 150005, MaxM = 5000005;
struct Edge{
    int destination, nextEdge, value;
}edge[MaxM * 2];
int n, m, C, A, B, cntEdge, head[MaxN], dis[MaxN];
bool visited[MaxN];
#define monoPair pair<int,int>
priority_queue< monoPair, vector< monoPair >, greater< monoPair > > q;

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
    edge[cntEdge].destination = v;
    edge[cntEdge].nextEdge = head[u];
    edge[cntEdge].value = w;
    head[u] = cntEdge;
    return;
}

inline void Dijkstra(int x){
    for(int i=1;i<=n;i++){
        visited[i] = false;
        dis[i] = INT_MAX;
    }
    dis[x] = 0;
    q.push(make_pair(0,x));
    for(int i=1;i<=n;i++){
        while(!q.empty() && visited[q.top().second]) q.pop();
        if(q.empty()) break;
        int u = q.top().second;
        q.pop();
        visited[u] = true;
        for(int j = head[u]; j; j = edge[j].nextEdge){
            int v = edge[j].destination, cost = edge[j].value;
            if(dis[v] > dis[u] + cost){
                dis[v] = dis[u] + cost;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}

signed main(){
    n = Read(), m = Read(), C = Read();
    for(int i=1;i<=m;i++){
        int u = Read(), v = Read(), w = Read();
        AddEdge(u, v, w);
    }
    int logn = floor(log2(n))+1;
    n = (1<<logn) - 1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<logn;j++)
            AddEdge(i, i^(1<<j), (1<<j)*C);
    A = Read(), B = Read();
    Dijkstra(A);
    printf("%lld", dis[B]);
    return 0;
}