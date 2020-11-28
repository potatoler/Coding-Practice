#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define ull unsigned long long
using namespace std;
const int threshold=10000000;
const int MaxN = 5000006;
int n, m, a[MaxN],b[MaxN];
ull k1,k2;
ull Rand(){
	ull k3=k1,k4=k2;
	k1=k4;
	k3^=(k3<<23);
	k2=k3^k4^(k3>>17)^(k4>>26);
	return k2+k4;
}
void gen(ull _k1, ull _k2){
	k1=_k1,k2=_k2;
	for(int i=1;i<=n;i++){
		a[i]=Rand()%threshold+1;
		b[i]=Rand()%threshold+1;
	}
}

signed main(){
//	freopen("hand.in", "r", stdin);
//	freopen("hand.out", "w", stdout);
	scanf("%lld%lld%llu%llu", &n, &m, &k1, &k2);
	gen(k1, k2);
	for(int i=1; i<=n; i++)
		b[i] += a[i];
	sort(a+1, a+1+n, greater<int>());
	sort(b+1, b+1+n, greater<int>());
	int ans = a[1], top = a[1];
	for(int i=3, j=2, k=1; i<=m; i+=2){
		int ans1 = 0, ans2 = 0;
		if(j < n) ans1 = a[j] + a[j+1];
		if(k <= n) ans2 = b[k];
		if(ans1 >= ans2) top += ans1, j += 2;
		else top += ans2, k++;
		ans ^= top;
	}
	top = 0;
	for(int i=2, j=1, k=1; i<=m; i+=2){
		int ans1 = 0, ans2 = 0;
		if(j < n) ans1 = a[j] + a[j+1];
		if(k <= n) ans2 = b[k];
		if(ans1 >= ans2) top += ans1, j += 2;
		else top += ans2, k++;
		ans ^= top;
	}
	printf("%lld", ans);
	return 0;
}