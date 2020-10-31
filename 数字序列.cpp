#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, ans, a[MaxN], b[MaxN];
int dis[MaxN], son[MaxN][2], cnt;
struct Node{
	int root, ls, rs, size, value;
}node[MaxN];

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

inline int Merge(int x, int y){
	if(!x || !y) return x+y;
	if(a[x] < a[y] || (a[x] == a[y] && x > y)) swap(x,y);
	son[x][1] = Merge(son[x][1], y);
	if(dis[son[x][0]] < dis[son[x][1]]) swap(son[x][0], son[x][1]);
	dis[x] = dis[son[x][1]] + 1;
	return x;
}

signed main(){
	n = Read();
	dis[0] = -1;
	for(int i=1; i<=n; i++)
		a[i] = Read()-i;
	for(int i=1; i<=n; i++){
		node[++cnt] = (Node){i,i,i,1,a[i]};
		while(cnt > 1 && node[cnt].value < node[cnt-1].value){
			cnt--;
			node[cnt].root = Merge(node[cnt].root, node[cnt+1].root);
			node[cnt].size += node[cnt+1].size;
			node[cnt].rs = node[cnt+1].rs;
			while(node[cnt].size*2 > node[cnt].rs-node[cnt].ls+2){
				node[cnt].size--;
				node[cnt].root = Merge(son[node[cnt].root][0], son[node[cnt].root][1]);
			}
			node[cnt].value = a[node[cnt].root];
		}
	}
	for(int i=1; i<=cnt; i++){
		for(int j = node[i].ls; j<=node[i].rs; j++){
			b[j] = node[i].value;
			ans += abs(a[j]-b[j]);
		}
	}
	printf("%lld\n", ans);
	for(int i=1; i<=n; i++)
		printf("%lld ", b[i]+i);
	return 0;
}