#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<cmath>
#define int long long
#define mod 1000000007
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 300005;
const int maxm = 600005;
struct edge{
	int to, next;
	bool cut;
}e[maxm];

int head[maxn], cnt, low[maxn], dfn[maxn], stk[maxn];
int indexx, top;
bool vis[maxn];
bool cut[maxn];
int add_block[maxn];
int bridge;

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

void Addedge(int u, int v){
	e[cnt].to = v;
	e[cnt].cut = 0;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

void Tarjan(int u, int pre){
	low[u] = dfn[u] = ++ indexx;
	stk[top ++] = u;
	vis[u] = 1;
	int son = 0;
	int pre_cnt = 0;
	for(int i = head[u]; ~i; i = e[i].next){
		int v = e[i].to;
		if(v == pre && pre_cnt == 0){
			pre_cnt ++;
			continue;
		}
		if(!dfn[v]){
			son ++;
			Tarjan(v, u);
			if(low[u] > low[v])
				low[u] = low[v];
			if(low[v] > dfn[u]){
				bridge ++;
				e[i].cut = 1;
				e[i^1].cut = 1;
			}
			if(u != pre && low[v] >= dfn[u]){
				cut[u] = 1;
				add_block[u] ++;
			}
		}
		else if(low[u] > dfn[v])
			low[u] = dfn[v];
	}
	if(u == pre && son > 1) cut[u] = 1;
	if(u == pre) add_block[u] = son - 1;
	vis[u] = 0;
	top --;
}

void Solve(int n){
	memset(dfn, 0, sizeof(dfn));
	memset(vis, 0, sizeof(vis));
	memset(add_block, 0, sizeof(add_block));
	memset(cut, 0, sizeof(cut
	));
	indexx = top = 0;
	bridge = 0;
	int num = 0;
	for(int i = 1; i <= n; i ++){
		if(! dfn[i]){
			Tarjan(i, i);
			num ++;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++) printf("%lld ", num + add_block[i]);

}
signed main(){
	int n = Read(), m = Read();
	memset(head, -1, sizeof(head));
	cnt = 0;
	while(m --){
		int u = Read(), v = Read();
		Addedge(u, v);
		Addedge(v, u);
	}
	Solve(n);
	return 0;
}

