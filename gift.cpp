#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003, Mod = 10000007;
int n, m;
int price[MaxN], sum[MaxN], f[MaxN], ans;

inline int Read(){
	int num  = 0, op = 1;
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

inline void Force(int k){
	int left = m - sum[k-1];
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for(int i=k+1; i<=n; i++)
		for(int j=left; j>=price[i]; j--)
			f[j] = (f[j] + f[j-price[i]]) % Mod;
	for(int i=max(left-price[k]+1,0ll); i<=left; i++)
		ans = (ans + f[i]) % Mod;
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		price[i] = Read();
	sort(price+1, price+1+n);
	for(int i=1; i<=n; i++)
		sum[i] = sum[i-1] + price[i];
	if(sum[n] <= m){
		printf("1");
		return 0;
	}
	for(int i=1; i<=n; i++){
		if(sum[i-1] > m) break;
		Force(i);
	}
	printf("%lld", ans);
	return 0;
}