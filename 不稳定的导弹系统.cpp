#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define ID1(x,y) (((x-1)*m+y)*2)
#define ID2(x,y) (((x-1)*m+y)*2-1)
using namespace std;
int n, m, ans, a[55][55], head[55*55*2], cntEdge=1, dis[55*55*2];
bool visited[55*55*2];
struct Edge{
	int destination, nextEdge, value;
}edge[55*55*4*2];

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
	return op * num;
}

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Link(int u, int v, int w){
	AddEdge(u, v, w);
	AddEdge(v, u, 0);
	return;
}

inline bool Check(){
	int res = INT_MAX;
	for(int i=0; i<=n*m*2+1; i++){
		if(visited[i]){
			for(int j = head[i]; j; j = edge[j].nextEdge){
				int to = edge[j].destination, val = edge[j].value;
				if(val && !visited[to]){
					res = min(res, dis[to]+1-dis[i]);
				}
			}
		}
	}
//	printf("%lld\n", res);
	if(res == INT_MAX) return false;
	for(int i=0; i<=n*m*2+1; i++){
		if(visited[i]) dis[i] += res;
	}
	return true;
}

inline int Update(int x, int y, int z){
	visited[x] = true;
//	printf("%lld\n", z);
	if(x == y){
		ans -= z;
		return z;
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int &to = edge[i].destination, &val = edge[i].value;
		if(!visited[to] && val && dis[x] == dis[to] + 1){
			int res = Update(to, y, min(z,val));
			if(res){
				edge[i].value -= res;
				edge[i^1].value += res;
				return res;
			}
		}
	}
	return 0;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			a[i][j] = Read();
			Link(ID1(i,j), ID2(i,j), INT_MAX);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int mx = 0;
			switch(a[i][j]){
				case -1:{
					Link(0, ID1(i,j), INT_MAX);
					for(int k=i; k>=1; k--)
						mx = max(mx, a[k][j]);
					for(int k=i; k>=2; k--)
						Link(ID1(k,j), ID1(k-1,j), mx-max(a[k][j],0ll));
					break;
				}
				case -2:{
					Link(0, ID1(i,j), INT_MAX);
					for(int k=i; k<=n; k++)
						mx = max(mx, a[k][j]);
					for(int k=i; k<n; k++)
						Link(ID1(k,j), ID1(k+1,j), mx-max(a[k][j],0ll));
					break;
				}
				case -3:{
					Link(ID2(i,j), n*m*2+1, INT_MAX);
					for(int k=j; k>=1; k--)
						mx = max(mx, a[i][k]);
					for(int k=j; k>=2; k--)
						Link(ID2(i,k-1), ID2(i,k), mx-max(a[i][k],0ll));
					break;
				}
				case -4:{
					Link(ID2(i,j), n*m*2+1, INT_MAX);
					for(int k=j; k<=m; k++)
						mx = max(mx, a[i][k]);
					for(int k=j; k<m; k++)
						Link(ID2(i,k+1), ID2(i,k), mx-max(a[i][k],0ll));
					break;
				}
			}
			ans += mx;
			Link(ID1(i,j), ID2(i,j), INT_MAX);
		}
	}
	do{
		memset(visited, false, sizeof(visited));
//		printf("O");
		while(Update(0, n*m*2+1, INT_MAX)){
//			printf("h");
			for(int i=0; i<=n*m*2+1; i++)
				visited[i] = false;
		}
//		printf("\n");
//		printf("%lld\n", ans);
	}while(Check());
	printf("%lld", ans);
	return 0;
}