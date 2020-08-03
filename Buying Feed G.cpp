#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MaxN = 505, MaxM = 10005;
ll k, e, n;
ll f[MaxN][MaxM], deque[MaxM];
struct Shop{
	ll x, f, c;
	bool operator < (const Shop &cmp)const{return x < cmp.x;}
}shop[MaxN];

inline ll Calculate(ll p, ll x){
	return f[p-1][x] + x * x * (shop[p].x-shop[p-1].x) - shop[p].c * x;
}

int main(){
	memset(f, 0x3f3f3f3f, sizeof(f));
	f[0][0] = 0;
	scanf("%lld%lld%lld",&k,&e,&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&shop[i].x, &shop[i].f, &shop[i].c);
	sort(shop+1, shop+1+n);
	for(int i=1;i<=n;i++){
		int head = 1, tail = 0;
		for(int j=0;j<=k;j++){
			while(head <= tail && Calculate(i, deque[tail]) > Calculate(i, j)) tail--;
			while(head <= tail && deque[head] < j-shop[i].f) head++;
			deque[++tail] = j;
			f[i][j] = Calculate(i, deque[head]) + shop[i].c * j;
		}
	}
	printf("%lld",f[n][k] + k * k * (e-shop[n].x));
	return 0;
}