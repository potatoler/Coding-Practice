#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 402;
int n, atk, a[MaxN], b[MaxN], h[MaxN], f[MaxN][MaxN];

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
	n = Read(), atk = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read(), b[i] = Read(), h[i] = Read();
	for(int i=1; i<=n; i++)
		f[i][i] = (a[i] + b[i-1] + b[i+1]) * (h[i] % atk ? h[i]/atk+1 : h[i]/atk);
	for(int len=1; len<=n; len++){
		for(int l=1; l+len<=n; l++){
			int r = l + len;
			f[l][r] = INT_MAX;
			for(int i=l; i<=r; i++){
				f[l][r] = min(f[l][r], f[l][i-1] + f[i+1][r] + (a[i]+b[l-1]+b[r+1]) * (h[i] % atk ? h[i]/atk+1 : h[i]/atk));
			}
		}
	}
	printf("%lld", f[1][n]);
	return 0;
}