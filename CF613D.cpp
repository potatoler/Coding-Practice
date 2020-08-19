#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <climits>
#include <utility>
#define int long long
using namespace std;
const int N = 1e6 + 9, M = 2 * N;
int n, m, pn, to[M], nt[M], hd[N];
int sz[N], id[N], son[N], fa[N];
int dp[N], q[N], st[N], h, tp[N];
int vn, vhd[N], vto[M], vnt[M], top;
bool vs[N], flg = true, g[N];
bool cmp(int x, int y)
{
	return id[x] < id[y];
}
void adve(int u, int v)
{
	vn++, vnt[vn] = vhd[u],
		  vhd[u] = vn, vto[vn] = v;
}
int rd()
{
	char c = getchar();
	int x = 0;
	while (c > 57 || c < 48)
		c = getchar();
	while (c > 47 && c < 58)
		x += (x << 3) + x + c - 48, c = getchar();
	return x;
}
void make(int x, int dep)
{
	dp[x] = dep, sz[x] = 1;
	for (int i = hd[x], v; i; i = nt[i])
	{
		if (to[i] == fa[x])
			continue;
		fa[v = to[i]] = x;
		make(v, dep + 1), sz[x] += sz[v];
		if (sz[v] > sz[son[x]])
			son[x] = v;
	}
}
void hvd(int x)
{
	id[x] = ++h;
	if (!tp[x])
		tp[x] = tp[fa[x]];
	if (!son[x])
		return;
	hvd(son[x]);
	for (int i = hd[x], v; i; i = nt[i])
	{
		if (id[v = to[i]])
			continue;
		tp[v] = v, hvd(v);
	}
}
int lca(int x, int y)
{
	while (tp[x] != tp[y])
		if (dp[tp[x]] > dp[tp[y]])
			x = fa[tp[x]];
		else
			y = fa[tp[y]];
	return dp[x] < dp[y] ? x : y;
}
int dfs(int x)
{
	int nm = 0, res = 0;
	for (int i = vhd[x]; i; i = vnt[i])
		res += dfs(vto[i]), nm += g[vto[i]];
	if (vs[x])
		res += nm, g[x] = true;
	else if (nm > 1)
		++res, g[x] = false;
	else
		g[x] = nm ? true : false;
	vhd[x] = 0, vs[x] = false;
	return res;
}
signed main()
{
	n = rd();
	for (int i = 1, u, v; i < n; ++i)
		u = rd(), v = rd(), nt[++pn] = hd[u],
		hd[u] = pn, to[pn] = v, to[++pn] = u,
		nt[pn] = hd[v], hd[v] = pn;
	tp[1] = 1, make(1, 1), hvd(1), m = rd();
	for (int k; m-- && (k = rd()); flg = 1)
	{
		for (int i = 1; i <= k; ++i)
			q[i] = rd(), vs[q[i]] = 1;
		for (int i = 1; i <= k; ++i)
			if (vs[fa[q[i]]])
				flg = 0;
		if (!flg)
		{
			for (int i = 1; i <= k; ++i)
				vs[q[i]] = 0;
			puts("-1");
			continue;
		}
		sort(q + 1, q + k + 1, cmp), st[top = 1] = q[1];
		for (int i = 2, z; i <= k; ++i)
		{
			z = lca(st[top], q[i]);
			while (dp[z] < dp[st[top - 1]])
				adve(st[top - 1], st[top]), top--;
			if (z != st[top])
			{
				adve(z, st[top]);
				if (st[top - 1] == z)
					top--;
				else
					st[top] = z;
			}
			st[++top] = q[i];
		}
		while (--top)
			adve(st[top], st[top + 1]);
		printf("%lld\n", dfs(st[1])), vn = 0;
	}
	return 0;
}