#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005, Mod = 571373;
int n, m, mod;
long long a[MaxN];
struct SegmentTree{
	int l, r;
	long long sumValue, addTag, mulTag;
}segtree[MaxN * 4];
inline void Build(int p, int l, int r){
	segtree[p].l = l;
	segtree[p].r = r;
	segtree[p].addTag = 0;
	segtree[p].mulTag = 1;
	if(l == r){
		segtree[p].sumValue = a[l] % Mod;
		return;
	}
	int mid = (l + r) / 2;
	Build(p*2, l, mid);
	Build(p*2+1, mid+1, r);
	segtree[p].sumValue = (segtree[p*2].sumValue + segtree[p*2+1].sumValue) % Mod;
}
inline void PassTag(int p){
	segtree[p*2].sumValue = ((segtree[p].mulTag * segtree[p*2].sumValue) % Mod + (segtree[p].addTag * (segtree[p*2].r - segtree[p*2].l + 1) % Mod)) % Mod;
	segtree[p*2+1].sumValue = ((segtree[p].mulTag * segtree[p*2+1].sumValue) % Mod + (segtree[p].addTag * (segtree[p*2+1].r - segtree[p*2+1].l + 1) % Mod)) % Mod;
	segtree[p*2].mulTag = (segtree[p].mulTag * segtree[p*2].mulTag) % Mod;
	segtree[p*2+1].mulTag = (segtree[p].mulTag * segtree[p*2+1].mulTag) % Mod;
	segtree[p*2].addTag = (segtree[p].addTag + segtree[p*2].addTag * segtree[p].mulTag) % Mod;
	segtree[p*2+1].addTag = (segtree[p].addTag + segtree[p*2+1].addTag * segtree[p].mulTag) % Mod;
	segtree[p].addTag = 0;
	segtree[p].mulTag = 1;
}
inline void Addition(int p, int l, int r, long long k){
	if(l <= segtree[p].l && r >= segtree[p].r){
		segtree[p].addTag = (segtree[p].addTag + k) % Mod;
		segtree[p].sumValue = (segtree[p].sumValue + k * (segtree[p].r - segtree[p].l + 1) % Mod) % Mod;
	}
	PassTag(p);
	segtree[p].sumValue = (segtree[p*2].sumValue + segtree[p*2+1].sumValue) % Mod;
	int mid = (segtree[p].l + segtree[p].r) / 2;
	if(l <= mid) Addition(p*2, l, r, k);
	if(r > mid) Addition(p*2+1, l, r, k);
	segtree[p].sumValue = (segtree[p*2].sumValue + segtree[p*2+1].sumValue) % Mod;
}
inline void Multiplication(int p, int l, int r, long long k){
	if(l <=  segtree[p].l && r >= segtree[p].r){
		segtree[p].addTag = (segtree[p].addTag * k) % Mod;
		segtree[p].mulTag = (segtree[p].mulTag * k) % Mod;
		segtree[p].sumValue = (segtree[p].sumValue * k) % Mod;
		return;
	}
	PassTag(p);
	segtree[p].sumValue = segtree[p*2].sumValue + segtree[p*2+1].sumValue;
	int mid = (segtree[p].r + segtree[p].l) / 2;
	if(l <= mid) Multiplication(p*2, l, r, k);
	if(r > mid) Multiplication(p*2+1, l, r, k);
	segtree[p].sumValue = segtree[p*2].sumValue + segtree[p*2+1].sumValue;
}
inline long long Ask(int p, int l, int r){
	if(l <= segtree[p].l && r >= segtree[p].r) return segtree[p].sumValue;
	PassTag(p);
	long long answer = 0;
	int mid = (segtree[p].l + segtree[p].r) / 2;
	if(l <= mid) answer = (answer + Ask(p*2, l, r)) % Mod;
	if(r > mid) answer = (answer + Ask(p*2+1, l, r)) % Mod;
	return answer;
}
int main(){
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	Build(1, 1, n);
	for(int i=1;i<=m;i++){
		int op, x, y;
		long long k;
		scanf("%d%d%d",&op,&x,&y);
		if(op == 1){
			scanf("%lld",&k);
			Multiplication(1, x, y, k);
		}
		else if(op == 2){
			scanf("%lld",&k);
			Addition(1, x, y, k);
		}
		else printf("%lld\n",Ask(1, x, y));
	}
	return 0;
}