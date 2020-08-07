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
const int MaxN = 100005;
int n, m, ans, sum[MaxN];
struct LeftistTree{
	int l, r, root, subtreeSize, dist;
}tree[MaxN];
struct Ninja{
	int boss, cost, ability;
}ninja[MaxN];

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

inline void Plant(int cur){
	tree[cur].subtreeSize = 1;
	tree[cur].root = cur;
	sum[cur] = ninja[cur].cost;
}

inline int Merge(int x, int y){
	if(!x || !y) return x+y;
	if(ninja[x].cost < ninja[y].cost) swap(x,y);
	tree[x].r = Merge(tree[x].r, y);
	if(tree[tree[x].l].dist < tree[tree[x].r].dist) swap(tree[x].l, tree[x].r);
	tree[x].dist = tree[tree[x].r].dist + 1;
	return x;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int b = Read(), c = Read(), l = Read();
		ninja[i] = (Ninja){b, c, l};
		ans = max(ninja[i].ability, ans);
		Plant(i);
	}
	for(int i=n; i>1; i--){
		int bo = ninja[i].boss;
		tree[bo].root = Merge(tree[i].root, tree[ninja[i].boss].root);
		tree[bo].subtreeSize += tree[i].subtreeSize;
		sum[bo] += sum[i];
		while(sum[bo] > m){
			sum[bo] -= ninja[tree[bo].root].cost;
			tree[bo].root = Merge(tree[tree[bo].root].l, tree[tree[bo].root].r);
			tree[bo].subtreeSize--;
		}
		ans = max(ans, ninja[bo].ability * tree[bo].subtreeSize);
	}
	printf("%lld", ans);
	return 0;
}
