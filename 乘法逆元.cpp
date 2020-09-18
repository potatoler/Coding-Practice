#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 3000006;
int inv[MaxN];
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
	int n = Read(), p = Read();
	inv[0] = 0, inv[1] = 1;
	for(int i=2; i<=n; i++)
		inv[i] = p - (p/i) * inv[p%i] % p;
	for(int i=1; i<=n; i++)
		printf("%lld\n", inv[i]);
	return 0;
}