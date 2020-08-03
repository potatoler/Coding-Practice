#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 155;
int n, m, d[MAXN], fir[MAXN], to[MAXN*MAXN], nxt[MAXN*MAXN], cnt;
inline void Add(int u, int v) { to[++cnt] = v, nxt[cnt] = fir[u], fir[u] = cnt, ++d[v]; }
int topo[MAXN], id[MAXN], cur, q[MAXN], s, t; //topo为拓扑序，id为topo的反函数
long long f[MAXN][MAXN], g[MAXN];
int main ()
{
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i)
		scanf("%d%d", &x, &y), Add(x, y);
	for(int i = 1; i <= n; ++i) if(!d[i]) q[t++] = i;
	while(s < t) //拓扑排序
	{
		int u = q[s++]; id[topo[u] = ++cur] = u;
		for(int i = fir[u]; i; i = nxt[i])
			if(--d[to[i]] == 0) q[t++] = to[i];
	}
	for(int i = 1, u; i <= n; ++i)
	{
		u = id[i]; f[u][u] = 1;
		for(int j = i, v; j <= n; ++j)
		{
			v = id[j];
			for(int k = fir[v]; k; k = nxt[k]) f[u][to[k]] += f[u][v];
		}
	}
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	for(int i = 1, u; i <= n; ++i)
	{
		u = id[i];
		g[u] = f[a][u] * f[c][u];
		for(int j = 1, v; j < i; ++j)
		{
			v = id[j];
			g[u] -= g[v] * f[v][u] * f[v][u];
		}
	}
	long long ans = f[a][b] * f[c][d];
	for(int i = 1, u; i <= n; ++i)
	{
		u = id[i];
		ans -= g[u] * f[u][b] * f[u][d];
	}
	printf("%lld\n", ans);
}
