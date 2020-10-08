#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, ans, lp, rp;
struct Cactus{
	int l, r;
	bool operator < (const Cactus &a) const{
		return l == a.l ? r<a.r : l<a.l;
	}
}cactus[MaxN];

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
	n = Read();
	for(int i=1; i<=n; i++){
		int p = Read(), h = Read();
		if(p < h){
			puts("-1");
			return 0;
		}
		cactus[i].l = max(0ll,p-h);
		cactus[i].r = p+h;
		if(i == n) cactus[i].r = h;
	}
	sort(cactus+1, cactus+1+n);
	lp = cactus[1].l, rp = cactus[1].r;
	for(int i=2; i<=n; i++){
		if(cactus[i].l < rp) rp = max(rp, cactus[i].r);
		else{
			ans = max(ans, rp-lp);
			lp = cactus[i].l;
			rp = cactus[i].r;
		}
	}
	ans = max(ans, rp-lp);
	double res = 1.0 * (double)ans/2.0;
	printf("%.1lf\n", res);
	return 0;
}