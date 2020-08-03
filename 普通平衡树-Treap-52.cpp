//#pragma GCC optimized(3)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, sum = 0, root = 0;
struct Treap{
	int subtreeSize, value, number, son[2], rand;
}treap[MaxN];

inline int read(){
	int x = 0, s = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-'){
			s = -1;
		}
		ch = getchar();
	}
	while (isdigit(ch)){
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * s;
}

inline void PushUp(int x){
	treap[x].subtreeSize = treap[treap[x].son[0]].subtreeSize + treap[treap[x].son[1]].subtreeSize + treap[x].number;
}

inline void Rotate(int &x, int d){
	int k = treap[x].son[d^1];
	treap[x].son[d^1] = treap[k].son[d];
	treap[k].son[d] = x;
	PushUp(x);
	PushUp(k);
	x = k;
}

inline void Insert(int &x, int y){
	if(!x){
		x = ++sum;
		treap[x].subtreeSize = treap[x].number = 1;
		treap[x].value = y;
		treap[x].rand = rand();
		return;
	}
	if(treap[x].value == y){
		treap[x].number++;
		treap[x].subtreeSize++;
		return;
	}
	int d = (y > treap[x].value);
	Insert(treap[x].son[d], y);
	if(treap[x].rand < treap[treap[x].son[d]].rand) Rotate(x, d^1);
	PushUp(x);
}

inline void Delete(int &x, int y){
	if(!x) return;
	if(y < treap[x].value) Delete(treap[x].son[0], y);
	else if(y > treap[x].value) Delete(treap[x].son[1], y);
	else{
		if(!treap[x].son[0] && !treap[x].son[1]){
			treap[x].number--;
			treap[x].subtreeSize--;
			if(treap[x].number == 0) x = 0;
		}
		else if(treap[x].son[0] && !treap[x].son[1]){
			Rotate(x, 1);
			Delete(treap[x].son[1], y);
		}
		else if(!treap[x].son[0] && treap[x].son[1]){
			Rotate(x, 0);
			Delete(treap[x].son[0], y);
		}
		else if(treap[x].son[0] && treap[x].son[1]){
			int d = (treap[treap[x].son[0]].rand > treap[treap[x].son[1]].rand);
			Rotate(x, d);
			Delete(treap[x].son[d], y);
		}
	}
	PushUp(x);
}

inline int Rank(int x, int y){
	if(!x) return 0;
	if(treap[x].value == y) return treap[treap[x].son[0]].subtreeSize + 1;
	else if(treap[x].value < y) return treap[treap[x].son[0]].subtreeSize + treap[x].number + Rank(treap[x].son[1], y);
	else return Rank(treap[x].son[0], y);
}

inline int Find(int x, int y){
	if(!x) return 0;
	if(treap[treap[x].son[0]].subtreeSize >= y) return Find(treap[x].son[0], y);
	else if(treap[treap[x].son[0]].subtreeSize + treap[x].number < y) return Find(treap[x].son[1], y - treap[x].number - treap[treap[x].son[0]].subtreeSize);
	else return treap[x].value;
}

inline int Predecessor(int x, int y){
	if(!x) return -INT_MAX;
	if(treap[x].value >= y) return Predecessor(treap[x].son[0], y);
	else return max(treap[x].value, Predecessor(treap[x].son[1], y));
}

inline int Successor(int x, int y){
	if(!x) return INT_MAX;
	if(treap[x].value <= y) return Successor(treap[x].son[1], y);
	else return min(treap[x].value, Successor(treap[x].son[0], y));
}

signed main(){
//	freopen("Treap.in","r",stdin);
//	freopen("std.out","w",stdout);
	n = read();
	while(n--){
		int op = read(), x = read();
		if(op == 1) Insert(root, x);
		else if(op == 2) Delete(root, x);
		else if(op == 3) printf("%lld\n", Rank(root, x));
		else if(op == 4) printf("%lld\n", Find(root, x));
		else if(op == 5) printf("%lld\n", Predecessor(root, x));
		else printf("%lld\n", Successor(root, x));
	}
	return 0;
}