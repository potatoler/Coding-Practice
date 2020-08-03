#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
struct SplayTree{
	int father[MaxN], son[MaxN][2], subtreeSize[MaxN], revTag[MaxN], root;
	
	inline void PushUp(int x){
		subtreeSize[x] = subtreeSize[son[x][0]] + subtreeSize[son[x][1]] + 1;
	}
	
	inline void PushDown(int x){
		if(revTag[x]){
			swap(son[x][0], son[x][1]);
			revTag[son[x][0]] ^= 1;
			revTag[son[x][1]] ^= 1;
			revTag[x] = 0;
		}
	}
	
	inline void Rotate(int x, int &k){
		int y = father[x], z = father[y], kind;
		if(son[y][0] == x) kind = 1;
		else kind = 0;
		if(y == k) k = x;
		else {
			if(son[z][0] == y) son[z][0] = x;
			else son[z][1] = x;
		}
		son[y][kind^1] = son[x][kind];
		father[son[y][kind^1]] = y;
		son[x][kind] = y;
		father[y] = x;
		father[x] = z;
		PushUp(x);
		PushUp(y);
	}
	
	inline void Splay(int x, int &k){
		while(x != k){
			int y = father[x], z = father[y];
			if(y != k){
				if((son[y][0] == x) ^ (son[z][0] == y)) Rotate(x, k);
				else Rotate(y, k);
			}
			Rotate(x, k);
		}
	}
	
	inline void Build(int l, int r, int f){
		if(l > r) return;
		int mid = (l + r) / 2;
		if(mid < f) son[f][0] = mid;
		else son[f][1] = mid;
		father[mid] = f;
		subtreeSize[mid] = 1;
		if(l == r) return;
		Build(l, mid-1, mid);
		Build(mid+1, r, mid);
		PushUp(mid);
	}
	
	inline int Find(int x, int k){
		PushDown(x);
		int s = subtreeSize[son[x][0]];
		if(k == s+1) return x;
		if(k <= s) return Find(son[x][0], k);
		else return Find(son[x][1], k-s-1);
	}
	
	inline void Reverse(int l, int r){
		int x = Find(root, l), y = Find(root, r+2);
		Splay(x, root);
		Splay(y, son[x][1]);
		int z = son[y][0];
		revTag[z] ^= 1;
	}
}splay;

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

signed main(){
	int n = read(), m = read();
	splay.root = (n + 3) / 2;
	splay.Build(1, n+2, splay.root);
	for(int i=1;i<=m;i++){
		int l = read(), r = read();
		splay.Reverse(l, r);
	}
	for(int i=2;i<=n+1;i++)
		printf("%lld ", splay.Find(splay.root, i)-1);
	return 0;
}