#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 30004, MaxD = 333;
int n, d, ans, cnt[MaxN], f[MaxN][MaxD*2+5], x;

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
	n = Read(), d = Read();
	for(int i=1; i<=n; i++){
		x = Read();
		cnt[x]++;
	}
	memset(f, -0x3f3f3f3f, sizeof(f));
	ans = f[d][MaxD] = cnt[0] + cnt[d];	
	for(int i=d+1; i<=x; i++){
		for(int j=-MaxD; j<=MaxD; j++){
			if(d+j > 0 && d+j <=i) f[i][MaxD+j] = max(f[i][MaxD+j], max(f[i-(d+j)][MaxD+j], max(f[i-(d+j)][MaxD+j-1],f[i-(d+j)][MaxD+j+1]))+cnt[i]);
			ans = max(ans, f[i][MaxD+j]);
		}
	}
	printf("%lld", ans);
	return 0;
}