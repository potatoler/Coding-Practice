#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
const long long Mod = 531373;
int n, m, mod;
long long a[MaxN];
struct SegmentTree{
	int l, r;
	long long sumValue, addTag, mulTag;
}segTree[MaxN * 4];
inline void Build(int p, int l, int r){
	segTree[p].l = l;
	segTree[p].r = r;
	segTree[p].addTag = 0;
	segTree[p].mulTag = 1;
	if(l == r) segTree[p].sumValue = a[l];
	else{
		int mid = (l + r) / 2;
		Build(p*2, l, mid);
		Build(p*2+1, mid+1, r);
		segTree[p].sumValue = segTree[p*2].sumValue + segTree[p*2+1].sumValue;
	}
	segTree[p].sumValue %= Mod;
	return;
}
inline void PassTag(int p){
	segTree[p*2].sumValue = (segTree[p*2].sumValue * segTree[p].mulTag + (segTree[p].addTag * (segTree[p*2].r - segTree[p*2].l + 1)) % Mod) % Mod;
	segTree[p*2+1].sumValue = (segTree[p*2+1].sumValue * segTree[p].mulTag + (segTree[p].addTag * (segTree[p*2+1].r - segTree[p*2+1].l + 1)) % Mod) % Mod;
	segTree[p*2].mulTag = (segTree[p*2].mulTag * segTree[p].mulTag) % Mod;
	segTree[p*2+1].mulTag = (segTree[p*2+1].mulTag * segTree[p].mulTag) % Mod;
	segTree[p*2].addTag = (segTree[p*2].addTag * segTree[p].mulTag + segTree[p].addTag) % Mod;
	segTree[p*2+1].addTag = (segTree[p*2+1].addTag * segTree[p].mulTag + segTree[p].addTag) %Mod;
	segTree[p].mulTag = 1;
	segTree[p].addTag = 0;
	return;
}
inline void Multiplication(int p, int l, int r, long long k){
	if(l <= segTree[p].l && r >= segTree[p].r){
		segTree[p].sumValue = (segTree[p].sumValue * k) % Mod;
		segTree[p].mulTag = (segTree[p].mulTag * k) % Mod;
		segTree[p].addTag = (segTree[p].addTag * k) % Mod;
		return;
	}
	PassTag(p);
	segTree[p].sumValue = (segTree[p*2].sumValue + segTree[p*2+1].sumValue) % Mod;
	int mid = (segTree[p].l + segTree[p].r) / 2;
	if(l <= mid) Multiplication(p*2, l, r, k);
	if(r > mid) Multiplication(p*2+1, l, r, k);
	segTree[p].sumValue = (segTree[p*2].sumValue + segTree[p*2+1].sumValue) % Mod;
	return;
}
inline void Addition(int p, int l, int r, long long k){
	if(l <= segTree[p].l && r >= segTree[p].r){
		segTree[p].addTag = (segTree[p].addTag + k) % Mod;
		segTree[p].sumValue = (segTree[p].sumValue + k * (segTree[p].r - segTree[p].l + 1)) % Mod;
		return;
	}
	PassTag(p);
	segTree[p].sumValue = (segTree[p*2].sumValue + segTree[p*2+1].sumValue) % Mod;
	int mid = (segTree[p].l + segTree[p].r) / 2;
	if(l <= mid) Addition(p*2, l, r, k);
	if(r > mid) Addition(p*2+1, l, r, k);
	segTree[p].sumValue = (segTree[p*2].sumValue + segTree[p*2+1].sumValue) % Mod;
	return;
}
inline long long Ask(int p, int l, int r){
	if(l <= segTree[p].l && r >= segTree[p].r) return segTree[p].sumValue;
	PassTag(p);
	int mid = (segTree[p].r + segTree[p].l) / 2;
	long long answer = 0;
	if(l <= mid) answer = (answer + Ask(p*2, l, r)) % Mod;
	if(r > mid) answer = (answer + Ask(p*2+1, l, r)) % Mod;
	return answer % Mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	Build(1, 1, n);
	while(m--){
		int op, l, r;
		long long k;
		scanf("%d%d%d",&op,&l,&r);
		if(op == 1){
			scanf("%lld",&k);
			Multiplication(1, l, r, k);
		}
		else if(op == 2){
			scanf("%lld",&k);
			Addition(1, l, r, k);
		}
		else printf("%lld\n",Ask(1, l, r));
	}
	return 0;
}