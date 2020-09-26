#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<algorithm>
#include<climits>
using namespace std;
const int MaxN = 100005;
int n, m, root, serial;
struct BBT{
	int son[2], father, value, size;
	bool reverse;
	void Init(int _value, int _father){
		value = _value, father = _father;
		size = 1;
	}
}tree[MaxN];

inline int Read(){
	int num  = 0, op = 1;
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

inline void Update(int x){
	tree[x].size = tree[tree[x].son[0]].size + tree[tree[x].son[1]].size + 1;
	return;
}

inline void PassTag(int x){
	if(tree[x].reverse){
		swap(tree[x].son[0], tree[x].son[1]);
		tree[tree[x].son[0]].reverse ^= 1;
		tree[tree[x].son[1]].reverse ^= 1;
		tree[x].reverse = 0;
	}
	return;
}

inline void Rotate(int x){
	int f = tree[x].father, g = tree[f].father; // father and grandfather
	int which = tree[f].son[1] == x; // which == 0? son[0] : son[1]
	tree[g].son[tree[g].son[1] == f] = x, tree[x].father = g;
	tree[f].son[which] = tree[x].son[which^1], tree[tree[x].son[which^1]].father = f;
	tree[x].son[which^1] = f, tree[f].father = x;
	Update(f), Update(x);
	// This rotate operation taking placing in g's subtree, information of g won't change;
	return;
}

inline void Splay(int x, int k){
	while(tree[x].father != k){
		int f = tree[x].father, g = tree[f].father;
		if(g != k){
			if((tree[f].son[1] == x) ^ (tree[g].son[1] == f)) Rotate(x);
			else Rotate(f);
		}
		Rotate(x);
	}
	if(!k) root = x;
	return;
}

inline void Insert(int w){
	int tar = root, fa = 0;
	while(tar){
		fa = tar;
		tar = tree[tar].son[w > tree[tar].value];
	}
	tar = ++serial;
	if(fa) tree[fa].son[w > tree[fa].value] = tar;
	tree[tar].Init(w, fa);
	Splay(tar, 0);
	return;
}

inline int GetKth(int k){
	int x = root;
	while(true){
		PassTag(x);
		if(tree[tree[x].son[0]].size >= k) x = tree[x].son[0];
		else if(tree[tree[x].son[0]].size + 1 == k) return x;
		else{
			k -= (tree[tree[x].son[0]].size + 1);
			x = tree[x].son[1];
		}
	}
	return -1;
}

inline void Print(int x){
	PassTag(x);
	if(tree[x].son[0]) Print(tree[x].son[0]);
	if(tree[x].value >= 1 && tree[x].value <= n) printf("%d ", tree[x].value);
	if(tree[x].son[1]) Print(tree[x].son[1]);
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=0; i<=n+1; i++)
		Insert(i);
	// Insert two barricades.
	while(m--){
		int l = Read(), r = Read();
		l = GetKth(l), r = GetKth(r+2);
		Splay(l, 0), Splay(r, l);
		tree[tree[r].son[0]].reverse ^= 1;
	}
//	for(int i=1; i<=serial; i++)
//		printf("%d %d\n", tree[i].value, tree[i].father);
	Print(root);
	return 0;
}