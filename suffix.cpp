#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, father[MaxN], val[MaxN], ans[MaxN], head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
int stack[MaxN], top;

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline int Find(int l, int r, int w){
	while(l < r){
		int mid = (l+r) >> 1;
		if(stack[mid] >= w) l = mid+1;
		else r = mid;
	}
	return l;
}

inline void DFS(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father[x]) continue;
		int tmp = top;
		int pos = -1, value = -1;
		if(val[y] > stack[top]){
			pos = Find(1, top, val[y]);
			value = stack[pos];
			stack[pos] = val[y];
			top = pos;
		}
		else{
			pos = top+1;
			value = stack[top+1];
			stack[++top] = val[y];
		}
		DFS(y);
		if(value != -1 && pos != -1){
			stack[pos] = value;
		}
		top = tmp;
	}
	ans[x] = top;
	return;
}

inline void Chain(){
	for(int i=1; i<=n; i++){
		while(top && val[stack[top]] < val[i])
			top--;
		stack[++top] = i;
		printf("%lld ", top);
	}
	return;
}

signed main(){
//	freopen("suffix.in", "r", stdin);
//	freopen("suffix.out", "w", stdout);
	n = Read();
	bool chain = true;
	for(int i=2; i<=n; i++){
		father[i] = Read();
		AddEdge(father[i], i);
		if(father[i] != i-1) chain = false;
	}
	for(int i=1; i<=n; i++)
		val[i] = Read();
	if(chain) Chain();
	else{
		stack[++top] = val[1];
		DFS(1);
		for(int i=1; i<=n; i++)
			printf("%lld ", ans[i]);
	}
	return 0;
}