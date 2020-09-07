#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, cntEdge, head[MaxN], restarmy_num, gap_num;
struct edge{
	int to, next;
	int w;
}edge[MaxN];
int garrison[MaxN], restnum[MaxN], restmin[MaxN], dis[MaxN][22], f[MaxN][22], used[MaxN], army[MaxN]; 
struct Vertex{
	int id, rest;
}rest_army[MaxN], gap[MaxN];

bool cmp(Vertex x, Vertex y) {
	return x.rest > y.rest;
}

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

inline void AddEdge(int x, int y, int z) {
	edge[++cntEdge].to = y;
	edge[cntEdge].w = z;
	edge[cntEdge].next = head[x];
	head[x] = cntEdge;
}

inline void DFS(int x, int fath, int len) {
	f[x][0] = fath;
	dis[x][0] = len;
	for (int i = 1; i <= 17; i++) {
		f[x][i] = f[f[x][i - 1]][i - 1];
		dis[x][i] = dis[x][i - 1] + dis[f[x][i - 1]][i - 1];
	}
	for (int i = head[x]; i; i = edge[i].next) {
		if (edge[i].to != fath) DFS(edge[i].to, x, edge[i].w);
	}
}

inline int Judge(int x, int fath) {
	bool no_gap = 1;
    bool have_son = 0;
	if (garrison[x]) return 1;
	
	for (int i = head[x]; i; i = edge[i].next) {
		if (edge[i].to == fath) continue;
		have_son = 1;
		if (!Judge(edge[i].to, x)) {
			no_gap = 0;
			if (x == 1) {
				gap[++gap_num].id = edge[i].to;
				gap[gap_num].rest = edge[i].w;
			}
			else return 0;
		}
	}
	if (!have_son) return 0;
	else return no_gap;
}


inline bool Check(int lim) {
	restarmy_num = 0;
	gap_num = 0;
	for (int i = 1; i <= n; i++) {
		garrison[i] = 0;
		restnum[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		used[i] = 0;
	}
	int num, x;
	for (int i = 1; i <= m; i++) {
		x = army[i];
		num = 0;
		for (int j = 17; j >= 0; j--) {
			if (f[x][j] > 1 && num + dis[x][j] <= lim) {
				num += dis[x][j];
				x = f[x][j];
			}
		}
		if (f[x][0] == 1 && lim - num - dis[x][0] >= 0) {
			rest_army[++restarmy_num].id = i;
			rest_army[restarmy_num].rest = lim - num - dis[x][0];
			if (!restnum[x] || restmin[x] > rest_army[restarmy_num].rest) {
				restnum[x] = i;
				restmin[x] = rest_army[restarmy_num].rest;
			}
		}
		else garrison[x] = 1;
	}
	if (Judge(1, 0)) return 1;
	sort(rest_army + 1, rest_army + restarmy_num + 1, cmp);
	sort(gap + 1, gap + gap_num + 1, cmp);
	used[0] = 1;
	int now = 1;
	for (int i = 1; i <= gap_num; i++) {
		if (!used[restnum[gap[i].id]]) {
			used[restnum[gap[i].id]] = 1;
			continue;
		}
	while (now <= restarmy_num && (used[rest_army[now].id] || rest_army[now].rest < gap[i].rest)) now++; 
		if (now > restarmy_num) return 0;
		used[rest_army[now].id] = 1;
	}
	return 1;
}

signed main(){
	n = Read();
	for (int i = 1; i <= n - 1; i++) {
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	DFS(1, 0, 0);
	m = Read();
	for (int i = 1; i <= m; i++)
		army[i] = Read();
	int l = 1, r = 500000;
	int ans = 0;
	int mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (Check(mid)) {
			r = mid - 1;
			ans = mid;
		}
		else l = mid + 1;
	}
	
	cout << ans << endl;
	return 0;
} 
