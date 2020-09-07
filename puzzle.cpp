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
int a[MaxN], n, t, tmp, ans, sum[MaxN], one, cnt[2];

inline void Read(int n){
	char ch = getchar();
	if (ch == '\r') {
		ch = getchar ();
	}
	for(int i=1; i<=n; i++){
		char ch = getchar();
		if (ch == '\r') {
			ch = getchar ();
		}
		if(ch == '1') a[i] = 1;
		else a[i] = 0;
		one += a[i];
	}
	return;
}

signed main(){
	scanf("%lld%lld", &t, &n);
	Read(n);
	// for(int i=1; i<=n; i++)
	// 	printf("%lld\n", a[i]);
	for(int i=n, j=one; i; i--){
		tmp++;
		if(a[i] == 1){
			sum[j--] = tmp;
			tmp = 0;
		}
	}
	// for(int i=1; i<=n; i++)
	// 	printf("%lld ", sum[i]);
	for(int i=1; i<=one; i++)
		cnt[i&1] += sum[i];
	tmp = 0;
	// for(int i=1; i<=n; i++)
 //        printf("%lld %lld\n", cnt[i&1], sum[i]);
	for(int i=1, j=1; i<=n; i++){
		tmp++;
		if(a[i] == 1){
			ans += (tmp-1) * (sum[j]-1) + tmp * (cnt[j&1]-sum[j]);
			cnt[j&1] -= sum[j];
			j++;
			tmp = 0;
		}
	}
	printf("%lld", ans);
	return 0;
}