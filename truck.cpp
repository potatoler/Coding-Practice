#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#define int long long
using namespace std;
template<class T1, class T2> T1& Cmax (T1 &a, const T2 &b){
	return a < b ? a = b : a;
}
template<class T1, class T2> T1& Cmin (T1 &a, const T2 &b){
	return a > b ? a = b : a;
}
const int MaxN = 300005, MaxM = 1000006, MaxLog = 20;
int n, m, q;
struct Edge{
	int from, to, value;
};
Edge graph[MaxM];
vector<Edge> mst[MaxN];

int path[MaxN][MaxLog], father[MaxN][MaxLog], depth[MaxN], non_tree[MaxN][MaxLog], tree[MaxN][MaxLog];
int idx[MaxN], back[MaxN];

inline bool cmp(Edge a, Edge b){
	return a.value < b.value;
}

class DSU{
	private:
	int father[MaxN];
	
	public:
	inline int Get(int x){
		return father[x] ? father[x] = Get(father[x]) : x;
	}
	
	inline void Merge(int x, int y){
		int fx = Get(x), fy = Get(y);
		if(fx != fy) father[fx] = fy;
		return;
	}
}dsu;

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

inline int Mex(int x, int y = -1){
	if(y == -1) return x == 0? 1 : 0;
	else if(x != 0 && y != 0) return 0;
	return (x|y) == 1? 2 : 1;
}

inline void Kruskal(){
	sort(graph+1, graph+1+m, cmp);
	memset(non_tree, 0x3f, sizeof(non_tree));
	for(int i=1; i<=m; i++){
		int &from = graph[i].from;
		int &to = graph[i].to;
		int &value = graph[i].value;
		if(dsu.Get(from) == dsu.Get(to)){
			Cmin(non_tree[from][0], value);
			Cmin(non_tree[to][0], value);
			continue;
		}
		dsu.Merge(from, to);
		mst[from].push_back((Edge){from, to, value});
		mst[to].push_back((Edge){to, from, value});
	}
	return;
}

inline void DFS(int x){
	mst[x].push_back((Edge){0, 0, INT_MAX});
	depth[x] = depth[father[x][0]] + 1;
	for(int i=1; i<20; i++){
		father[x][i] = father[father[x][i-1]][i-1];
		path[x][i] = max(path[x][i-1], path[father[x][i-1]][i-1]);
		tree[x][i] = min(tree[x][i-1], tree[father[x][i-1]][i-1]);
		non_tree[x][i] = min(non_tree[x][i-1], non_tree[father[x][i-1]][i-1]);
	}
	for(int i=0; i<=(int)mst[x].size()-2; i++){
		if(mst[x][i].to == father[x][0]){
			idx[x] = i;
			break;
		}
	}
//	printf("%lu ", mst[x].size());
	for(int i=0; i<=(int)mst[x].size()-2; i++){
		int &to = mst[x][i].to, &value = mst[x][i].value;
		if(i == idx[x]) continue;
		back[to] = i;
//		printf("%lld\n", back[to]);
		father[to][0] = x;
		path[to][0] = value;
		tree[to][0] = mst[x][Mex(i,idx[x])].value;
		DFS(to);
	}
}

inline void LCA(int x, int y, int &tmp_path, int &tmp_tree, int &tmp_non){
	tmp_path = 0, tmp_non = INT_MAX;
	if(depth[x] < depth[y]) swap(x,y);
	tmp_tree = mst[x][Mex(idx[x])].value;
	for(int i=19; i>=0; i--){
		if(depth[father[x][i]] >= depth[y]){
			Cmax(tmp_path, path[x][i]);
			Cmin(tmp_non, non_tree[x][i]);
			Cmin(tmp_tree, tree[x][i]);
			x = father[x][i];
		}
	}
	if(x == y){
		Cmin(tmp_non, non_tree[x][0]);
		Cmin(tmp_tree, mst[x][idx[x]].value);
		return;
	}
	Cmin(tmp_tree, mst[y][Mex(idx[y])].value);
	for(int i=19; i>=0; i--){
		if(father[x][i] != father[y][i]){
			Cmax(tmp_path, max(path[x][i], path[y][i]));
			Cmin(tmp_non, min(non_tree[x][i], non_tree[y][i]));
			Cmin(tmp_tree, min(tree[x][i], tree[y][i]));
			x = father[x][i];
			y = father[y][i];
		}
	}
	Cmax(tmp_path, max(path[x][0], path[y][0]));
	int fa = father[x][0];
	Cmin(tmp_non, non_tree[fa][0]);
	Cmin(tmp_tree, mst[fa][Mex(back[x], back[y])].value);
	return;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		graph[i] = (Edge){u,v,w};
	}
	Kruskal();
	idx[1] = mst[1].size();
	memset(tree[1], 0x3f, sizeof(tree[1]));
	DFS(1);
	for(int i=1; i<=q; i++){
		int x = Read(), y = Read();
		int tmp_path = 0, tmp_non = 0, tmp_tree = 0;
		LCA(x, y, tmp_path, tmp_tree, tmp_non);
		Cmax(tmp_path, min(tmp_tree, tmp_non));
		printf("%lld\n", tmp_path != INT_MAX? tmp_path : -1);
	}
	return 0;
}