#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102;
int n, m, d[MaxN][2], f[MaxN][MaxN];

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
//	freopen("software.in", "r", stdin);
//	freopen("software.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		d[i][0] = Read(), d[i][1] = Read();
	int l = 0, r = 10000;
	while(l < r){
		int mid = (l+r) >> 1;
		for(int i=0; i<=n; i++)
			for(int j=0; j<=m; j++)
				f[i][j] = -INT_MAX;
		f[0][0] = 0;
		for(int i=1; i<=n; i++){
			for(int j=0; j<=m; j++){
				for(int k=0; k<=min(j, mid/d[i][0]); k++){
					f[i][j] = max(f[i][j], f[i-1][j-k] + (mid-d[i][0]*k)/d[i][1]);
				}
			}
		}
		if(f[n][m] >= m) r = mid;
		else l = mid+1;
	}
	printf("%lld", l);
	return 0;
}