#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 802;
int n, m, x[MaxN], y[MaxN];
char map[MaxN][MaxN];

inline int Calculate(int len, int (&a)[MaxN]){
	int sum1, sum2, ans1, ans2, res;
	sum1 = sum2 = ans1 = ans2 = res = 0;
	for(int i=2; i<=len; i++){
		sum1 += a[i];
		ans1 += (i-1) * a[i];
	}
	res = ans1;
	for(int i=2; i<=len; i++){
		sum2 += a[i-1];
		ans2 += sum2;
		ans1 -= sum1;
		sum1 -= a[i];
		res = min(res, ans1 + ans2);
	}
	return res;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1; i<=n; i++)
		scanf("%s", map[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(map[i][j] == '*') x[i]++, y[j]++;
	int ans = Calculate(n, x) + Calculate(m, y);
	printf("%lld", ans);
}