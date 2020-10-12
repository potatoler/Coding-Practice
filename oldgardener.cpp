#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 998244353;
int n, m, a[MaxN], sumcut[MaxN], cut[MaxN];
struct SegmentTree{
	int l, r, sum, tag, ori, rev;
}tree[MaxN*4];
#define thisTree tree[x]
#define leftySon tree[x*2]
#define rightSon tree[x*2+1]
#define range (tree[x].r - tree[x].l + 1)

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

inline void Update(int x){
	thisTree.sum = leftySon.sum ^ rightSon.sum;
	thisTree.rev = leftySon.rev | rightSon.rev;
	thisTree.ori = leftySon.ori | rightSon.ori;
	return;
}

inline void Change(int x, int y){
	thisTree.tag ^= y;
	if(range & 1) thisTree.sum ^= y;
	int tmp;
	for(int i=0; i<30; i++){
		if((y>>i) & 1){
			tmp = (thisTree.rev>>i) & 1;
			thisTree.rev &= ~(1<<i);
			thisTree.rev |= thisTree.ori & (1<<i);
			thisTree.ori &= ~(1<<i);
			thisTree.ori |= (tmp<<i);
		}
	}
}

inline void PassTag(int x){
	if(!thisTree.tag) return;
	Change(x*2, thisTree.tag);
	Change(x*2+1, thisTree.tag);
	thisTree.tag = 0;
	return;
}

inline void Build(int x, int l, int r){
	thisTree.l = l, thisTree.r = r;
	if(l == r){
		thisTree.sum = a[l];
		if(cut[l]){
			thisTree.ori = a[l];
			thisTree.rev = ((1<<30) - 1) ^ a[l];
		}
		return;
	}
	int mid = (l + r) >> 1;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	Update(x);
	return;
}

inline void Modify(int x, int ql, int qr, int y){
	if(ql <= thisTree.l && thisTree.r <= qr){
		Change(x, y);
		return;
	}
	int mid = (thisTree.l + thisTree.r) >> 1;
	PassTag(x);
	if(ql <= mid) Modify(x*2, ql, qr, y);
	if(qr > mid) Modify(x*2+1, ql, qr, y);
	Update(x);
	return;
}

int answer, record;
inline void Query(int x, int ql, int qr){
	if(ql <= thisTree.l && thisTree.r <= qr){
		answer ^= thisTree.sum;
		record |= thisTree.ori;
		return;
	}
	int mid = (thisTree.l + thisTree.r) >> 1;
	PassTag(x);
	if(ql <= mid) Query(x*2, ql, qr);
	if(qr > mid) Query(x*2+1, ql, qr);
	return;
}

signed main(){
//	freopen("oldgardener.in", "r", stdin);
//	freopen("oldgardener.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		cut[i] = Read()? 0 : 1;
		sumcut[i] = sumcut[i-1] + cut[i];
	}
	for(int i=1; i<=n; i++)
		a[i] = Read();
	Build(1, 1, n);
	while(m--){
		int op = Read(), l = Read(), r = Read();
		if(op == 1){
			int y = Read();
			Modify(1, l, r, y);
		}
		else{
			if(sumcut[r] - sumcut[l-1] == 0){
				puts("0");
				continue;
			}
			answer = record = 0;
			int res = 0, last = 0, tmp = 0;
			Query(1, l, r);
//			printf("%lld %lld ", answer, record);
			for(int i=1; i<30; i++)
				if((record>>i) & 1) tmp = (tmp + (1<<(i-1)) % Mod) % Mod;
//			printf("%lld\n", tmp);
			for(int i=0; i<30; i++){
				if(i && ((record>>i) & 1)) tmp = (tmp - (1<<(i-1)) % Mod + Mod) % Mod;
				if((answer>>i) & 1) res = (res + (last + tmp) * (1<<i) % Mod) % Mod;
				else{
					if((record>>i) & 1) res = (res + ((1<<i) + tmp) * (1<<i) % Mod) % Mod;
					else res = (res + tmp * (1<<i) % Mod) % Mod;
				}
				if((record>>i) & 1) last = (last + (1<<i) % Mod) % Mod;
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}