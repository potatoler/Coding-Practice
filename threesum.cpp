#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 5003, MaxA = 2000006, Stand = 1000000;
int N, Q, a[MaxN], f[MaxN][MaxN], bucket[MaxA];

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
	freopen("threesum.in", "r", stdin);
	freopen("threesum.out", "w", stdout);
	N = Read(), Q = Read();
	for(int i=1; i<=N; i++){
		a[i] = Read();
		a[i] += Stand;
	}
	for(int i=1; i<=N; i++){
		for(int j=i+1; j<=N; j++){
			if(j > i+1){
				if(a[i] + a[j] <= Stand * 3 && a[i] + a[j] >= Stand) f[i][j] = bucket[Stand * 3 - a[i] - a[j]];
			}
			bucket[a[j]]++;
		}
		for(int j=i+1; j<=N; j++)
			bucket[a[j]]--;
	}
//	for(int i=1; i<=N ;i++){
//			for(int j=1; j<=N; j++){
//				printf("%lld ",f[i][j]);
//			}
//			printf("\n");
//		}
	for(int i=1; i<=N; ++i)
		for(int j=1; j<=N; ++j)
			f[i][j] += f[i-1][j] + f[i][j-1] - f[i-1][j-1];
	while(Q--){
		int l = Read(), r = Read();
		printf("%lld\n", f[r][r] - f[l-1][r] - f[r][l-1] + f[l-1][l-1]);
	}
	return 0;
}