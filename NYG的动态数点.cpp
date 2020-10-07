#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, lg[MaxN], ans[MaxN], a[MaxN], gcd[35][MaxN], mn[35][MaxN], value, cnt;
struct Unit{
	int gcd, mn;
};

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

inline int GCD(int x, int y){
	return y == 0 ? x : GCD(y, x%y);
}

inline Unit GetUnit(int x, int len){
	Unit ans;
	ans.gcd = GCD(gcd[lg[len]][x], gcd[lg[len]][x+len-(1<<lg[len])]);
	ans.mn = min(mn[lg[len]][x], mn[lg[len]][x+len-(1<<lg[len])]);
	return ans;
}

inline bool Check(int x){
	Unit tmp;
	for(int i=1; i<=n-x+1; i++){
		tmp = GetUnit(i, x);
		if(tmp.gcd == tmp.mn) return true;
	}
	return false;
}

inline void UpdateAnswer(){
	Unit tmp;
	for(int i=1; i<=n-value+1; i++){
		tmp = GetUnit(i, value);
		if(tmp.gcd == tmp.mn) ans[++cnt] = i;
	}
}

signed main(){
	n = Read();
	lg[0] = -1;
	for(int i=1; i<=n; i++){
		a[i] = Read();
		lg[i] = lg[i>>1] + 1;
		gcd[0][i] = mn[0][i] = a[i];
	}
	for(int i=1; i<=lg[n]; i++){
		for(int j=1; j<=n-(1<<i)+1; j++){
			gcd[i][j] = GCD(gcd[i-1][j], gcd[i-1][j+(1<<(i-1))]);
			mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<(i-1))]);
		}
	}		
	int l = 1, r = n;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(Check(mid)){
			value = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	for(int i=1; i<=n-value+1; i++){
		Unit tmp = GetUnit(i, value);
		if(tmp.gcd == tmp.mn) ans[++cnt] = i;
	}
	printf("%lld %lld\n", cnt, value-1);
	for(int i=1; i<=cnt; i++)
		printf("%lld ", ans[i]);
	return 0;
}