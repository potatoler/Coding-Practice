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
int n, m, num[MaxN], tree[MaxN];

inline int Lowbit(int x){
	return x & -x;
}

inline void Add(int x, int k){
	while(x <= n){
		tree[x] += k;
		x += Lowbit(x);
	}
}

inline int Search(int x){
	int ans = 0;
	while(x != 0){
		ans += tree[x];
		x -= Lowbit(x);
	}
	return ans;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&num[i]);
	for(int i=1;i<=m;i++){
		int a;
		scanf("%lld",&a);
		if(a == 1){
			int x, y, z;
			scanf("%lld%lld%lld", &x, &y,&z);
			Add(x, z); Add(y+1, -z);
		}
		if(a == 2){
			int x;
			scanf("%lld", &x);
			printf("%lld\n", num[x] + Search(x));
		}
	}
	return 0;
}