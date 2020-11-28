#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<map>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m, father[MaxN][30], lg[MaxN], depth[MaxN];
struct Edge{
	int u,v,w;
}edge[MaxN];
class DSU{
public:
	int belong[MaxN], size[MaxN];
	inline int Find(int, int*);
	inline void Merge1(int, int);
	inline void Merge2(int, int);
}dsu1, dsu2;
vector<int> destination[MaxN];
map<int,int> type[MaxN];

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

inline void DFS(int x){
	depth[x] = depth[father[x][0]] + 1;
	for(int i=1; i<=lg[depth[x]]; i++)
		father[x][i] = father[father[x][i-1]][i-1];
	for(auto y : destination[x]){
		if(y == father[x][0]) continue;
		father[y][0] = x;
		dsu1.size[x]++;
		DFS(y);
	}
	return;
}

inline int LCA(int x, int y){
	if(depth[x] > depth[y]) swap(x,y);
	int delta = depth[y] - depth[x];
	for(int i = lg[delta]; i>=0; i--)
		if(delta & (1<<i)) y = father[y][i];
	if(x == y) return x;
	for(int i = lg[depth[x]]; i>=0; i--){
		if(father[x][i] != father[y][i]){
			x = father[x][i];
			y = father[y][i];
		}
	}
	return father[x][0];
}

inline int DSU::Find(int x, int *fa){
	return fa[x] == x ? x : Find(fa[x], fa);
}

inline void DSU::Merge1(int x, int y){
	if(depth[x] > depth[y]) swap(x,y);
	x = Find(x, belong);
	belong[y] = x;
	size[x] += size[y];
	return;
}

inline void DSU::Merge2(int x, int y){
	auto &self = *this;
	if(depth[x] > depth[y]) swap(x,y);
	dsu1.size[Find(x, dsu1.belong)] -= self.size[y];
	x = Find(x, self.belong);
	self.belong[y] = x;
	self.size[x] += self.size[y];
	if(father[x][0]) dsu1.size[Find(father[x][0], dsu1.belong)] += self.size[y];
	return;
}

inline bool Arrive(int s, int t){
	int lca = LCA(s,t), x = dsu2.Find(s, dsu2.belong), y = dsu1.Find(t, dsu1.belong);
//		printf("%lld ", lca);
//	cout << s << t << endl;
	if(depth[x] <= depth[lca] && depth[y] <= depth[lca]) return true;
	else if(depth[x] > depth[lca] && dsu1.Find(father[x][0], dsu1.belong) == y) return true;
	else if(depth[y] > depth[lca] && dsu2.Find(father[y][0], dsu2.belong) == x) return true;
	else return false;
}

signed main(){
//	freopen("brain.in","r",stdin);
//	freopen("brain.out","w",stdout);
	n = Read(), m = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		edge[i] = {u,v,w};
		destination[u].push_back(v);
		destination[v].push_back(u);
		type[u][v] = type[v][u] = w;
	}
//	for(int i=1; i<=n; i++){
//		for(auto y : destination[i]){
//			printf("%lld ", y);
//		}
//		printf("\n");
//	}
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<17; j++){
//			printf("%lld ", father[i][j]);
//		}
//		printf("\n");
//	}
	for(int i=2; i<=n; i++)
		lg[i] = lg[i>>1] + 1;
	DFS(1);
	for(int i=1; i<=n; i++){
		dsu1.belong[i] = dsu2.belong[i] = i;
		dsu2.size[i] = 1;
	}
	for(int i=1; i<n; i++){
		int &u = edge[i].u, &v = edge[i].v, &w = edge[i].w;
		if(w <= 2) dsu2.Merge2(u,v);
		if(w == 1) dsu1.Merge1(u,v);
	}
	for(int i=1; i<=m; i++){
		int a = Read(), b = Read(), t = Read(), s = Read();
		if(type[a][b] >= 2){
			type[a][b]--, type[b][a]--;
			if(type[a][b] == 2) dsu2.Merge2(a,b);
			else dsu1.Merge1(a,b);
		}
//		for(int i=1;i<=n;i++)cout<<dsu1.size[i]<<" "<<dsu2.size[i]<<endl;
		int ifArrive = Arrive(s,t);
		int x = dsu1.Find(t, dsu1.belong);
		int cntX = dsu2.size[dsu2.Find(t,dsu2.belong)] + dsu1.size[x];
//		cout<<x<<"*"<<father[x][0]<<" "<<type[x][father[x][0]]<<endl;
		if(father[x][0] && type[x][father[x][0]] == 3) cntX += dsu2.size[dsu2.Find(father[x][0], dsu2.belong)];
		printf("%lld %lld\n", ifArrive, cntX);
	}
	return 0;
}

