#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, len, head[MaxN], cntEdge, depth[MaxN], sequence[MaxN],top, first[MaxN], last[MaxN], cnt[MaxN], state[MaxN], ans[MaxN], value[MaxN], queue[MaxN], f[MaxN][16];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Query{
	int ID, l, r, lca;
}query[MaxN];
vector<int> num;
#define thisSon edge[i].destination

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

inline int Locate(int x){
	return x / len;
}

inline bool cmp(const Query &x, const Query &y){
	int xpos = Locate(x.l), ypos = Locate(y.l);
	if(xpos != ypos) return xpos < ypos;
	return x.r < y.r;
}

inline void AddEgde(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int x, int father){
	sequence[++top] = x;
	first[x] = top;
	for(int i = head[x]; i; i = edge[i].nextEdge)
		if(thisSon != father) DFS(thisSon, x);
	sequence[++top] = x;
	last[x] = top;
}

inline void BFS(){
	memset(depth, 0x3f, sizeof(depth));
	depth[0] = 0, depth[1] = 1;
	int hd = 0, tl = 0;
	queue[0] = 1;
	while(hd <= tl){
		int x = queue[hd++];
		for(int i = head[x]; i; i = edge[i].nextEdge){
			if(depth[thisSon] > depth[x] + 1){
				depth[thisSon] = depth[x] + 1;
				f[thisSon][0] = x;
				for(int j=1; j<16; j++)
					f[thisSon][j] = f[f[thisSon][j-1]][j-1];
				queue[++tl] = thisSon;
			}
		}
	}
}

inline int LCA(int x, int y){
	if(depth[x] < depth[y]) swap(x, y);
	for(int i=15; i>=0; i--)
		if(depth[f[x][i]] >= depth[y]) x = f[x][i];
	if(x == y) return x;
	for(int i=15; i>=0; i--)
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

inline void Add(int x, int &res){
	state[x] ^= 1;
	if(!state[x]){
		cnt[value[x]]--;
		if(!cnt[value[x]]) res--;
	}
	else{
		if(!cnt[value[x]]) res++;
		cnt[value[x]]++;
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		num.push_back(value[i] = Read());
	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end());
	for(int i=1; i<=n; i++)
		value[i] = lower_bound(num.begin(), num.end(), value[i]) - num.begin();
//	for(int i=1; i<=n; i++)
//		printf("%lld ", value[i]);
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEgde(u, v), AddEgde(v, u);
	}
	DFS(1,0);
	BFS();
	len = sqrt(top);
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		if(first[u] > first[v]) swap(u, v);
		int lca = LCA(u,v);
		if(u == lca) query[i] = {i, first[u], first[v]};
		else query[i] = {i, last[u], first[v], lca};
	}
	sort(query+1, query+1+m, cmp);
	int L = 1, R = 0, res = 0;		
	for(int i=1; i<=m; i++){
//		printf("%lld %lld %lld %lld\n", query[i].ID, query[i].l, query[i].r, query[i].lca);
		int ID = query[i].ID, l = query[i].l, r = query[i].r, lca = query[i].lca;
		while(R < r) Add(sequence[++R], res);
		while(R > r) Add(sequence[R--], res);
		while(L < l) Add(sequence[L++], res);
		while(L > l) Add(sequence[--L], res);
		if(lca) Add(lca, res);
		ans[ID] = res;
		if(lca) Add(lca, res);
	}
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}