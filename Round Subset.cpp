#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 202, MaxLog = 20004;
int n, k, two[MaxN], five[MaxN], f[MaxN][MaxLog], ans;

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

inline void Divide(int cnt, int x){
	while(x % 2 == 0){
		two[cnt]++;
		x /= 2;
	}
	while(x % 5 == 0){
		five[cnt]++;
		x /= 5;
	}
	return;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		int a = Read();
		Divide(i, a);
	}
	memset(f, -0x3f3f3f, sizeof(f));
	f[0][0] = 0;
	int sum = 0;
	for(int l=1; l<=n; l++){
		sum += five[l];
		for(int i=min(k,l); i>=1; i--){
			for(int j = sum; j>=five[l]; j--)
				f[i][j] = max(f[i][j], f[i-1][j-five[l]] + two[l]);
		}
	}
	for(int i=1; i<=min(k,n); i++)
		for(int j=0; j<=sum; j++)
			ans = max(ans, min(j, f[i][j]));
	printf("%lld", ans);
	return 0;
}