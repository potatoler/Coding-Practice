#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, MaxM = 21, S = 1<<20;
int T, n, m, c, b, q, f[S];

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
//	freopen("night.in", "r", stdin);
//	freopen("night.out", "w", stdout);
	T = Read();
	while(T--){
		n = Read(), m = Read();
		memset(f, 0, sizeof(f));
		for(int i=1; i<=n; i++){
			int x = Read();
			f[x]++;
		}
		b = 1;
		c = Read();
		while(c--){
			int x = Read();
			b |= 1<<x;
		}
		while(b<(1<<m)){
			for(int i=(1<<m)-1; i>=1; i--)
				if((i&b) == b) f[i^b] += f[i];
			b<<=1;
		}
		q = Read();
		while(q--){
			int x = Read();
			printf("%lld\n", f[x]);
		}
	}
	return 0;
}