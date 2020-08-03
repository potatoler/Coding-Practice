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
const int MaxN = 300005;
int n, mn, ans;
struct SplayTree{
	int father[MaxN], son[MaxN][2], subtreeSize[MaxN], number[MaxN], value[MaxN], root, tot;
	inline bool Identify(int x){
		return son[father[x]][1] == x;
	}
	
	inline void Update(int x){
		subtreeSize[x] = subtreeSize[son[x][0]] + subtreeSize[son[x][1]] + number[x];
	}
	
	inline void Rotate(int x){
		int fa = father[x], gfa = father[fa];
		int d = Identify(x), s = son[x][d^1];
		son[fa][d] = s, father[s] = fa;
		son[gfa][Identify(fa)] = x; father[x] = gfa;
		son[x][d^1] = fa, father[fa] = x;
		Update(fa), Update(x);
	}
	
	inline void Splay(int x){
		while(father[x] != 0){
			int fa = father[x], gfa = father[fa];
			if(gfa != 0){
				if(Identify(x) == Identify(fa)) Rotate(fa);
				else Rotate(x);
			}
			Rotate(x);
		}
		root = x;
	}
	
	inline void Insert(int x){
		if(x < mn) return;
		int r = root, p = 0;
		while(value[r] != x && r){
			p = r;
			r = son[r][x > value[r]];
		}
		if(r) number[r]++;
		else{
			r = ++tot;
			if(p) son[p][x > value[p]] = r;
			father[r] = p;
			son[r][0] = son[r][1] = 0;
			subtreeSize[r] = number[r] = 1;
			value[r] = x;
		}
		Splay(r);
	}
	
	inline void Find(int x){
		int r = root;
		while(x != value[r] && son[r][x > value[r]]) r = son[r][x > value[r]];
		Splay(r);
	}
	
	inline void Plus(int x){
		for(int i=1;i<=tot;i++)
			value[i] += x;
	}
	
	inline void Minus(int x){
		for(int i=1;i<=tot;i++)
			value[i] -= x;
	}
	
	inline int Get(int x){
		Find(x);
		if(value[root] >= x) return root;
		int r = son[root][1];
		while(son[r][0]) r = son[r][0];
		return r;
	}
	
	inline void Delete(int x){
		int r = Get(x + mn);
		Splay(r);
		ans += subtreeSize[son[r][0]];
		son[r][0] = 0;
		Update(r);
		Minus(x);
	}
	
	inline int Kth(int k){
		if(k >= subtreeSize[root]) return -1;
		k++;
		int r = root;
		while(1){
			if(son[r][1] && k <= subtreeSize[son[r][1]]) r = son[r][1];
			else if(k > subtreeSize[son[r][1]] + number[r]){
				k = k - subtreeSize[son[r][1]] - number[r];
				r = son[r][0];
			}
			else return value[r];
		}
	}
}splay;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op  = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	n = Read(), mn = Read();
	splay.Insert(INT_MAX);
	while(n--){
		char op[5];
		scanf("%s", op);
		int x = Read();
		if(op[0] == 'I') splay.Insert(x);
		else if(op[0] == 'A') splay.Plus(x);
		else if(op[0] == 'S') splay.Delete(x);
		else printf("%lld\n", splay.Kth(x));
//		for(int i=1;i<=n;i++)
//			printf("%lld ", splay.value[i]);
//		printf("\n");
	}
	printf("%lld\n", ans);
	return 0;
}