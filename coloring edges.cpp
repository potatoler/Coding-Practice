#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1000005;
int n,m,cnt,now,q,f[maxn],d[maxn],col[maxn];
struct edge{
    int x,y,c;
}e[maxn];
int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) f[i]=i;
    for (int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        e[i].x=x,e[i].y=y,e[i].c=z;
        if (z) now-=d[x]+d[y],d[x]^=1,d[y]^=1,now+=d[x]+d[y];
        if (find(x)!=find(y)) f[find(x)]=find(y);
    }
    for (int i=1;i<=m;i++)
        if (e[i].c){
            int x=find(e[i].x);
            if (!col[x]) cnt++;
            col[x]++;
        }
    scanf("%d",&q);
    for (int op,x;q;q--){
        scanf("%d",&op);
        if (op==2) printf("%d\n",now?-1:cnt);
        else{
            scanf("%d",&x),x++;
            now-=d[e[x].x]+d[e[x].y],d[e[x].x]^=1;d[e[x].y]^=1,now+=d[e[x].x]+d[e[x].y];
            if (e[x].c){
                e[x].c=0,col[find(e[x].x)]--;
                if (!col[find(e[x].x)]) cnt--;
            }
            else{
                e[x].c=1;
                if (!col[find(e[x].x)]) cnt++;
                col[find(e[x].x)]++;
            }
        }
    }
    return 0;
}