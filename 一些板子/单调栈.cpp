#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 3000006;
int n, a[MaxN], f[MaxN], stack[MaxN], top;

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
		a[i] = Read();
	for(int i=1; i<=n; i++){
		while(top && a[stack[top]] < a[i])
			f[stack[top--]] = i;
		stack[++top] = i;
	}
	for(int i=1; i<=n; i++)
		printf("%lld ", f[i]);
	return 0;
}