#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 6004;
struct Portal{
    int x,y;
}portal[MaxN * 1000];
int n, m, k, cntEdge, ans = INT_MAX;
int head[MaxN], nxt[MaxN], to[MaxN], val[MaxN];
int a[MaxN], dis[MaxN][1030];

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

inline void AddEdge(int x,int y,int z){
    nxt[++cntEdge]=head[x];
    head[x]=cntEdge;
    to[cntEdge]=y;
    val[cntEdge]=z;
    return;
}

int main(){
	// freopen("room.in", "r", stdin);
	// freopen("room.out", "w", stdout);
    n = Read(),m = Read(),k = Read();
    for(int i=1;i<=n;i++)
        for(int j=0;j<k;j++)
          a[i] += Read()<<j;
    for(int i=1;i<=m;i++){
        int x = Read(), y = Read(), z = 0;
        for(int j=0;j<k;j++) z += Read()<<j;
        AddEdge(x,y,z);
    }
    memset(dis,0x3f,sizeof(dis));
    int l = 0, r = 1;
    dis[1][a[1]] = 0;
    portal[1].x = 1, portal[1].y = a[1];
    while(l<r){
        Portal now = portal[++l], t;
        for(int i = head[now.x]; i; i = nxt[i])
            if((now.y&val[i]) == val[i] && dis[now.x][now.y]+1 < dis[to[i]][now.y|a[to[i]]]){
                dis[to[i]][now.y|a[to[i]]] = dis[now.x][now.y]+1;
                if(to[i] == n) ans = min(ans, dis[to[i]][now.y|a[to[i]]]);
                t.x = to[i], t.y = now.y|a[to[i]];
                portal[++r] = t;
            }
    }
    if(ans == INT_MAX) printf("No Solution");
    else printf("%d", ans);
    return 0;
}