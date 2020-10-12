#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 102, INF = LLONG_MAX/2;
int n, m, T, f[61][MaxN][MaxN], record[MaxN], tmp[MaxN], ans, limit;

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
	T = Read();
	while(T--){
		n = Read(), m = Read();
		ans = limit = 0;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++){
				f[0][i][j] = Read();
				if(!f[0][i][j]) f[0][i][j] = -INF;
			}	
//		for(int i=1; i<=n; i++){
//			for(int j=1; j<=n; j++){
//				printf("%lld ", f[0][i][j]);
//			}
//			printf("\n");
//		}
		for(int k=1; k<=60; k++){
			bool arrive = false;
			for(int i=1; i<=n; i++){
				for(int j=1; j<=n; j++){
					f[k][i][j] = -INF;
					for(int l=1; l<=n; l++)
						f[k][i][j] = max(f[k][i][j], f[k-1][i][l]+f[k-1][l][j]);
				}
			}
			for(int i=1; i<=n; i++){
				if(f[k][1][i] >= m){
					arrive = true;
					break;
				}
			}
			if(arrive){
				limit = k;
				break;
			}
		}
		for(int i=1; i<=n; i++)
			record[i] = f[limit-1][1][i];
//		for(int i=1; i<=n; i++)
//			printf("%lld ", record[i]);
		ans += (1ll<<(limit-1));
		for(int k=limit-2; k>=0; k--){
			bool arrive = true;
			for(int i=1; i<=n; i++){
				tmp[i] = -INF;
				for(int j=1; j<=n; j++)
					tmp[i] = max(tmp[i], record[j] + f[k][j][i]);
			}
			for(int i=1; i<=n; i++)
				if(tmp[i] >= m) arrive = false;
			if(arrive){
				memcpy(record, tmp, sizeof(record));
				ans += (1ll<<k);
			}
		}
		printf("%lld\n", ans+1);
	}
	return 0;
}