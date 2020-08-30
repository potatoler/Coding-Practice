#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 21;
int f[MaxN][MaxN][2], used[MaxN];

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

inline void Init(){
	f[1][1][1] = f[1][1][0] = 1;
	for(int i=2; i<MaxN; i++)
		for(int j=1; j<=i; j++){
			for(int k=1; k<j; k++)
				f[i][j][1] += f[i - 1][k][0];
			for(int k=j; k<i; k++)
				f[i][j][0] += f[i - 1][k][1];
		}
}

signed main(){
	Init();
	int T = Read();
	while(T--){
		memset(used, 0, sizeof used);
		int n = Read(), c = Read();
		int last, k;
		for(int j=1; j<=n;j++){
			if(f[n][j][1] >= c){
				last = j, k = 1;
				break;
			}
			else c -= f[n][j][1];
			if(f[n][j][0] >= c){
				last = j, k = 0;
				break;
			}
			else c -= f[n][j][0];
		}
		used[last] = 1;
		printf("%lld", last);
		for(int i = 2; i <= n; i++){
			k ^= 1;
			int rank = 0;
			for(int j=1; j<=n; j++){
				if (used[j]) continue;
				rank++;
				if((j < last && k == 0) || (j > last && k == 1)){
					if(f[n - i + 1][rank][k] >= c){
						last = j;
						used[last] = 1;
						printf(" %lld", last);
						break;
					}
					else c -= f[n - i + 1][rank][k];
				}
			}
		}
		printf("\n");
	}

	return 0;
}