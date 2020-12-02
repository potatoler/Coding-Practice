#include <cstdio>
//基础的头文件
#include <algorithm>
//给sort开的头文件
#define INF 1917483645
using namespace std;

int vis[20], lev[20], d[20];
//vis : 已经访问过的点
//lev : 点距离初始点的距离
//d : 通过此点可以达到的点数
int c[20][20], tar[20][20];
//c : 费用
//tar ：存下每个点能到的点
/*为什么要特意存下每个点到的点？
答案其实并不困难，加快访问速度*/

int ans = INF, tmp, tot, cnt, n, m, p;
//ans : 最终的答案
//tmp : 最优解剪枝用
//tot : dfs储存中间答案的用具
//cnt ：现在已经访问过的点数
//n : 点数
//m : 边数
//p : sort用品

inline bool cmp(int a, int b) {
    return c[p][a] < c[p][b];
    //按照费用给每个点能到的点排序
}

inline void dfs(int num, int node) {
    for(int i = num; i <= cnt; i ++) {
        //由第几个被访问的点来扩展
        if(tot + tmp * lev[vis[i]] >= ans) return;
        //最优性剪枝，如果当前解加上理论最小的费用都比中途的答案高
        //那么这次搜索一定不是最优解
        for(int j = node; j <= d[vis[i]]; j ++)
        //下一步扩展谁
        if(!lev[tar[vis[i]][j]]) { //用lev同时充当标记，有lev代表已访问
            cnt ++; //多添加一个点
            vis[cnt] = tar[vis[i]][j]; //记录这个点
            tmp -= c[vis[cnt]][tar[vis[cnt]][1]]; //理论最小的更新
            tot += c[vis[i]][vis[cnt]] * lev[vis[i]]; //加上当前的影响
            lev[vis[cnt]] = lev[vis[i]] + 1; //因为从vis[i]拓展，故lev一定为其 + 1
            dfs(i, j + 1); //继续从i枚举, 注意到tar[i][1 ~ j]已全部访问，下一次从j + 1尝试访问
            tot -= c[vis[i]][vis[cnt]] * lev[vis[i]]; //回溯
            lev[vis[cnt]] = 0; //回溯
            tmp += c[vis[cnt]][tar[vis[cnt]][1]]; //回溯
            cnt --; //回溯
        }
        node = 1; //剪枝别剪错了，i枚举玩下次还要从1枚举
    }
    if(cnt == n) { //已经访问了n个点，更新答案
        if(tot < ans) ans = tot;
        return;
    }
}

int main() {
    int u, v, w;
    scanf("%d%d", &n, &m); //读入n, m
    for(int i = 1; i <= n; i ++)
    for(int j = 1; j <= n; j ++)
    c[i][j] = INF; //初始赋无限大，方便后面的操作
    for(int i = 1; i <= m; i ++) {
        scanf("%d%d%d", &u, &v, &w); //这个w先暂时存起来
        //因为发现m = 1000 远> n * n，所以要剪掉一些边
        if(c[u][v] < w) continue; //w不能更新c[u][v]
        if(c[u][v] == INF) //第一次更新c[u][v]，统计u,v的出度
        tar[u][++ d[u]] = v, tar[v][++ d[v]] = u;
        c[u][v] = c[v][u] = w;
    }
    for(int i = 1; i <= n; i ++) {
        p = i; //sort排序cmp
        sort(tar[i] + 1, tar[i] + 1 + d[i], cmp);
        tmp += c[i][tar[i][1]]; //因为每个点总要扩展一条边，
        //因此我们把最小的边找出来,作为最优性剪枝
        //不仅如此，因为边越小作为最终解的可能性越大
        //实际上在一定程度上优化了程序
    }
    for(int i = 1; i <= n; i ++) {
        tot = 0; cnt = 1; //赋初值
        vis[1] = i; //第一个就选i
        tmp -= c[i][tar[i][1]]; //i的最优性剪枝的影响要去掉
        //因为剪枝的时候是以还未访问和还未将被访问的点为基础的
        //不去掉剪枝就是错误的
        lev[i] = 1; //赋值
        dfs(1, 1); //只有一个点，也肯定是从1枚举
        lev[i] = 0; //回溯
        tmp += c[i][tar[i][1]];
    }
    printf("%d", ans);
    return 0;
}