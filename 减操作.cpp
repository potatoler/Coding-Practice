#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 10001;
int n, t, a[102], f[102][MaxN*3], answer[102];

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

inline void DP(){
	f[1][a[1]+MaxN] = 1;
	f[2][a[1]-a[2]+MaxN] = -1;
	for(int i=3; i<=n; i++){
		for(int j=1; j<=MaxN+10000; j++){
			if(f[i-1][j] != 0){
				f[i][j+a[i]] = 1;
				f[i][j-a[i]] = -1;
			}
		}
	}
}

inline void Print(){
	int s = t + MaxN;
	for(int i=n; i>=1; i--){
		answer[i] = f[i][s];
		s -= answer[i] * a[i];
	}
	int cnt = 0;
	for(int i=2; i<=n; i++){
		if(answer[i] == 1){
			printf("%lld\n", i-cnt-1);
			cnt++;
		}
	}
	for(; cnt<n-1; cnt++)
		printf("1\n");
}

signed main(){
	n = Read(), t = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	DP();
	Print();
	return 0;
}