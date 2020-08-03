#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500010;
int n, m, tree[MaxN];

inline int Lowbit(int k){
	return k & -k;
}

inline void Add(int x, int k){
	while(x <= n){
		tree[x] += k;
		x += Lowbit(x);
	}
}

inline int Sum(int x){
	int ans = 0;
	while(x != 0){
		ans += tree[x];
		x -= Lowbit(x);
	}
	return ans;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%lld",&a);
		Add(i, a);
	}
	for(int i=1;i<=m;i++){
		int a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if(a == 1) Add(b, c);
		if(a == 2) printf("%lld\n", Sum(c) - Sum(b-1));
	}
	return 0;
}