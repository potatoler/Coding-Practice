#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
//#define int long long
#define Serial(x,y) ((x-1)*m+y)
#define lowbit(x) (x&(-x));
using namespace std;
const int MaxN = 55, dirx[4] = {-1, 1, 0, 0}, diry[4] = {0, 0, -1, 1};
int n, m, T, dis[20][20], tmp[MaxN][MaxN], f[1<<20][20];
char mp[MaxN][MaxN];
struct Point{
    int x, y;
}gift[20], king, queen;
int cntGift;
bool visited[MaxN][MaxN];
queue<Point> q;

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

inline int Count(int x){
    int res = 0;
    while(x){
        x -= lowbit(x);
        res++;
    }
    return res;
}

inline void BFS(Point s, int serial){
    memset(visited, false, sizeof(visited));
    memset(tmp, 0, sizeof(tmp));
    while(q.size())
        q.pop();
    q.push(s);
    visited[s.x][s.y] = true;
    for(q.push(s); !q.empty(); q.pop()){
        Point cur = q.front();
        for(int i=0; i<4; i++){
            int nxt = cur.x + dirx[i], nyt = cur.y + diry[i];
            if(nxt >= 0 && nxt < n && nyt >= 0 && nyt < m && !visited[nxt][nyt] && mp[nxt][nyt] != '#'){
                tmp[nxt][nyt] = tmp[cur.x][cur.y] + 1;
                q.push((Point){nxt,nyt});
                visited[nxt][nyt] = true;
            }
        }
    }
    for(int i=0; i<cntGift; i++)
        dis[serial][i] = tmp[gift[i].x][gift[i].y];
}

signed main(){
//    freopen("gift.in", "r", stdin);
//    freopen("gift.out", "w", stdout);
    n = Read(), m = Read(), T = Read();
    for(int i=0; i<n; i++)
        scanf("%s", mp[i]);
    memset(tmp, 0x3f3f3f3f, sizeof(tmp));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            switch(mp[i][j]){
                case 'G':{
                    gift[cntGift++] = {i,j};
                    break;
                }
                case 'K':{
                    king = {i,j};
                    break;
                }
                case 'Q':{
                    queen = {i,j};
                    break;
                }
            }
        }
    }
    gift[cntGift++] = king, gift[cntGift++] = queen;
    for(int i=0; i<cntGift; i++)
        BFS(gift[i], i);
//    for(int i=0; i<cntGift; i++)
//        printf("%lld %lld\n", gift[i].x, gift[i].y);
//    printf("\n\n");
//    for(int i=0; i<cntGift; i++){
//        for(int j=0; j<cntGift; j++){
//            printf("%lld ", dis[i][j]);
//        }
//        printf("\n");
//    }
    int limit = 1 << (cntGift-2), ans = 0;
    memset(f, 0x3f3f3f3f, sizeof(f));
    for(int i=0; i<(cntGift-2); i++)
        f[1<<i][i] = dis[cntGift-2][i];
    for(int i=0; i<limit; i++){
        for(int j=0; j<(cntGift-2); j++){
            if((1<<j) & i){
                for(int k=0; k<(cntGift-2); k++){
                    if(j != k && ((1<<k) & i) && dis[j][k]){
                        f[i][j] = min(f[i][j], f[i-(1<<j)][k] + Count(i) * dis[j][k]);
                    }
                }
            }
        }
    }
    for(int i=0; i<limit; i++){
        for(int j=0; j<(cntGift-2); j++){
            if(dis[j][cntGift-1]){
                int cost = f[i][j] + (Count(i) + 1) * dis[j][cntGift-1];
                if(cost <= T) ans = max(ans, Count(i));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}