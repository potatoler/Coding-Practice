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
const int MaxN = 20004, MaxQ = 100005;
int n, m, q, cntEdge, head[MaxN], dist[MaxN], ans[MaxQ];
int xIndex[MaxN], yIndex[MaxN], cntSerial;
int queue[MaxN * 140]; bool inque[MaxN];
#define serial(i,j) ((i-1) * m + j)
struct Edge{
    int destination, nextEdge, value;
}edge[MaxN * 4];
struct Query{
    int x1, x2, y1, y2, ID;
}query[MaxQ], tmp[MaxQ];

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

inline void Dijkstra(int st, int xl, int xr, int yl, int yr, int last){
    int dis = dist[st];
    for(int i=xl; i<=xr; i++)
        for(int j=yl; j<=yr; j++)
            dist[serial(i,j)] = last? dist[serial(i,j)] + dis:INT_MAX;
    dist[st] = 0; inque[st] = true;
    int l = 10000, r = 10000;
    queue[r++] = st;
    while(l != r){
        int u = queue[l++];
        inque[u] = false;
        for(int i = head[u]; i; i = edge[i].nextEdge){
            int v = edge[i].destination, vx = xIndex[v], vy = yIndex[v];
            if(vx >= xl && vx <= xr && vy >= yl && vy <= yr){
                if(dist[v] > dist[u] + edge[i].value){
                    dist[v] = dist[u] + edge[i].value;
                    if(!inque[v]){
                        if(dist[v] <= dist[queue[l]]) queue[--l] = v;
                        else queue[r++] = v;
                        inque[v] = true;
                    }
                }
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++)
    //         printf("%lld ", dist[serial(i,j)]);
    //     printf("\n");
    // } 
}

inline void Solve(int xl, int xr, int yl, int yr, int ql, int qr){
    if(ql > qr) return;
    if(xr - xl > yr - yl){
        int mid = (xl + xr) / 2;
        for(int i=yl; i<=yr; i++){
            Dijkstra(serial(mid,i), xl, xr, yl, yr, i-yl);
            for(int j=ql; j<=qr; j++) ans[query[j].ID] = min(ans[query[j].ID], dist[serial(query[j].x1,query[j].y1)] + dist[serial(query[j].x2,query[j].y2)]);
        }
        int l = ql - 1, r = qr + 1;
        for(int i=ql; i<=qr; i++){
            if(query[i].x1 < mid && query[i].x2 < mid) tmp[++l] = query[i];
            else if(query[i].x1 > mid && query[i].x2 > mid) tmp[--r] = query[i];
        }
        for(int i=ql; i<=l; i++) query[i] = tmp[i];
        for(int i=r; i<=qr; i++) query[i] = tmp[i];
        Solve(xl, mid-1, yl, yr, ql, l);
        Solve(mid+1, xr, yl, yr, r, qr);
    }
    else{
        int mid = (yl + yr) / 2;
        for(int i=xl; i<=xr; i++){
            Dijkstra(serial(i,mid), xl, xr, yl, yr, i-xl);
            for(int j=ql; j<=qr; j++) ans[query[j].ID] = min(ans[query[j].ID], dist[serial(query[j].x1,query[j].y1)] + dist[serial(query[j].x2,query[j].y2)]);
        }
        int l = ql - 1, r = qr + 1;
        for(int i=ql; i<=qr; i++){
            if(query[i].y1 < mid && query[i].y2 < mid) tmp[++l] = query[i];
            else if(query[i].y1 > mid && query[i].y2 > mid) tmp[--r] = query[i];
        }
        for(int i=ql; i<=l; i++) query[i] = tmp[i];
        for(int i=r; i<=qr; i++) query[i] = tmp[i];
        Solve(xl, xr, yl, mid-1, ql, l);
        Solve(xl, xr, mid+1, yr, r, qr);
    }
    // for(int i=1; i<=q; i++)
    //     printf("%lld ", ans[i]);
    // printf("\n");
    return;
}

signed main(){
    memset(ans, 0x3f, sizeof(ans));
    n = Read(), m = Read();
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            xIndex[++cntSerial] = i, yIndex[cntSerial] = j;
    for(int i=1; i<=n; i++)
        for(int j=1; j<m; j++){
            int val = Read();
            AddEdge(serial(i,j), serial(i,j+1), val);
            AddEdge(serial(i,j+1), serial(i,j), val);
        }
    for(int i=1; i<n; i++)
        for(int j=1; j<=m; j++){
            int val = Read();
            AddEdge(serial(i,j), serial(i+1,j), val);
            AddEdge(serial(i+1,j), serial(i,j), val);
        }
    q = Read();
    for(int i=1; i<=q; i++){
        query[i].x1 = Read(), query[i].y1 = Read(), query[i].x2 = Read(), query[i].y2 = Read();
        query[i].ID = i;
    }
    Solve(1, n, 1, m, 1, q);
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++)
    //         printf("(%lld,%lld) ", xIndex[serial(i,j)], yIndex[serial(i,j)]);
    //     printf("\n");
    // } 
    for(int i=1; i<=q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}