#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m;
struct LeftistTree{
	int l, r, value, dist, root;
}tree[MaxN];

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

//inline int Swap(int &x, int &y){
//	x ^= y ^= x ^= y;
//}

inline int GetRoot(int x){
	return tree[x].root == x? x : tree[x].root = GetRoot(tree[x].root);
}

inline int Merge(int x, int y){
	if(!x || !y) return x + y;
	if(tree[x].value > tree[y].value || (tree[x].value == tree[y].value && x > y)) swap(x,y);
	tree[x].r = Merge(tree[x].r, y);
	if(tree[tree[x].r].dist > tree[tree[x].l].dist) swap(tree[x].l, tree[x].r);
	tree[tree[x].l].root = tree[tree[x].r].root = tree[x].root = x;
	tree[x].dist = tree[tree[x].r].dist + 1;
	return x;
}

inline void Pop(int x){
	tree[x].value = -1;
	tree[tree[x].l].root = tree[x].l, tree[tree[x].r].root = tree[x].r;
	tree[x].root = Merge(tree[x].l, tree[x].r);
}

signed main(){
	n = Read(), m = Read();
	tree[0].dist = -1;
	for(int i=1; i<=n; i++){
		tree[i].root = i;
		tree[i].value = Read();
	}
	while(m--){
		int oprt = Read();
		if(oprt == 1){
			int x = Read(), y = Read();
			if(tree[x].value == -1 || tree[y].value == -1) continue;
			int xRoot = GetRoot(x), yRoot = GetRoot(y);
			if(xRoot != yRoot) tree[xRoot].root = tree[yRoot].root = Merge(xRoot, yRoot);
		}
		else{
			int x = Read();
			if(tree[x].value == -1){
				printf("-1\n");
				continue;
			}
			printf("%lld\n", tree[GetRoot(x)].value);
			Pop(GetRoot(x));
		}
	}
	return 0;
}