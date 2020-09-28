#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 10000007;
int n, a[MaxN], stack[MaxN], top, pos, lson[MaxN], rson[MaxN], ansl, ansr;

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
	for(int i=1; i<=n; i++){
		a[i] = Read();
		pos = top;
		while(pos && a[stack[pos]] > a[i]) pos--;
		if(pos) rson[stack[pos]] = i;
		if(pos < top) lson[i] = stack[pos+1];
		stack[top=++pos] = i;
	}
	for(int i=1; i<=n; i++){
		ansl ^= i*(lson[i]+1);
		ansr ^= i*(rson[i]+1);
	}
	printf("%lld %lld", ansl, ansr);
	return 0;
}