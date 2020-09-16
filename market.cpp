#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, maxTime;
struct Shop{
	int c, v, t;
}shop[MaxN];
struct Plan{
	int T, M, ID;
}plan[MaxN];
int f[MaxN], ans[MaxN];

bool cmpShop(Shop x, Shop y){
	return x.t < y.t;
}

bool cmpPlan(Plan x, Plan y){
	return x.T < y.T;
}

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

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		shop[i].c = Read(), shop[i].v = Read(), shop[i].t = Read();
	for(int i=1; i<=m; i++){
		plan[i].T = Read(), plan[i].M = Read();
		plan[i].ID = i;	
	}
	sort(plan+1, plan+1+m, cmpPlan);
	sort(shop+1, shop+1+n,cmpShop);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	int j = 1;
	for(int i=1; i<=m; i++){
		while(j<=n && shop[j].t <= plan[i].T){
			for(int k = n*300; k>=shop[j].v; k--)
				f[k] = min(f[k], f[k-shop[j].v] + shop[j].c);
			for(int k=n*300; k; k--)
				f[k] = min(f[k], f[k+1]);
			j++;
		}
		ans[plan[i].ID] = upper_bound(f+1, f+n*300+1, plan[i].M) - f-1;
	}
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}