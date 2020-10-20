#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, m, a[MaxN], mn[MaxN], pos, cnt, ans, sum[MaxN], f[MaxN];
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
	for(int i=0; i<m; i++)
		a[i] = Read();
	mn[m-1] = a[m-1];
	for(int i=m-2; i>=0; i--)
		mn[i] = min(mn[i+1]+1, a[i]);
	mn[m-1] = min(mn[m-1], mn[0]+1);
	for(int i=m-2; i>=0; i--)
		mn[i] = min(mn[i+1]+1, a[i]);
//	for(int i=0; i<m; i++)
//		printf("%lld ", mn[i]);
	while(!f[pos]){
		f[pos] = cnt;
		cnt++;
		sum[cnt] = sum[cnt-1] + mn[pos];
		pos = (pos + mn[pos]) % m;
	}
//	for(int i=0; i<m; i++)
//		printf("%lld ", sum[f[i]]);
	if(n <= f[pos]) ans = sum[n];
	else ans = sum[f[pos]] + (n-f[pos]) / (cnt-f[pos]) * (sum[cnt]-sum[f[pos]]) + sum[f[pos] + (n-f[pos]) % (cnt-f[pos])]-sum[f[pos]];
	printf("%lld", ans);
	return 0;
}