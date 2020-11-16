#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, p, f[MaxN], dis[MaxN], tree[MaxN], cntNode, uniqueNode, board[MaxN], ans;
struct Node{
	int x, y, kind, board;
	inline bool operator < (const Node &tmp)const{
		if(x != tmp.x) return x < tmp.x;
		if(y != tmp.y) return y < tmp.y;
		return kind < tmp.kind;
	}
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

inline int LowBit(int x){
	return x & -x;
}

inline void Add(int x, int val){
	for( ; x<=uniqueNode; x+=LowBit(x)) tree[x] = max(tree[x], val);
	return;
}

inline int Ask(int x){
	int res = 0;
	for( ; x; x-=LowBit(x)) res = max(res, tree[x]);
	return res;
}

signed main(){
//	freopen("boards.in", "r", stdin);
//	freopen("boards.out", "w", stdout);
	n = Read(), p = Read();
	for(int i=1; i<=p; i++){
		int x = Read(), y = Read();
		node[++cntNode] = (Node){x, y, 0, i};
		board[cntNode] = y;
		dis[i] -= x + y;
		x = Read(), y = Read();
		node[++cntNode] = (Node){x, y, 1, i};
		board[cntNode] = y;
		dis[i] += x+y;
	}
	node[++cntNode] = (Node){n, n, 2, 0};
	sort(board+1, board+1+cntNode);
	uniqueNode = unique(board+1, board+cntNode+1) - board - 1;
	for(int i=1; i<=cntNode; i++)
		node[i].y = lower_bound(board+1, board+uniqueNode+1, node[i].y) - board;
	sort(node+1, node+1+cntNode);
	for(int i=1; i<=cntNode; i++){
		if(node[i].kind == 2){
			for(int j=1; j<=p; j++)
				if(node[i].x >= node[j].x && node[i].y >= node[j].y) ans = max(ans, f[j]);
			printf("%lld\n", 2*n - ans);
			return 0;
		}
		else if(!node[i].kind) f[node[i].board] = Ask(node[i].y) + dis[node[i].board];
		else Add(node[i].y, f[node[i].board]);
	}
	return 0;
}