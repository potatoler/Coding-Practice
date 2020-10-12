#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1003;
int n, L[MaxN], D[MaxN], f[MaxN];

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
	n = Read();
	for(int i=1; i<=n; i++)
		L[i] = Read();
	for(int i=1; i<=n; i++)
		D[i] = Read();
	for(int i=1; i<=n; i++)
		for(int j=n; j>=L[i]; j--)
			f[j] = max(f[j], f[j-L[i]] + D[i]);
	printf("%lld", f[n]);
	return 0;
}