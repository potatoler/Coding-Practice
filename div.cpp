#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, a[MaxN], ans[202], cntDivisor;

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

inline void Divide(int x){
	for(int i=1; i*i<=x; i++){
		if(x % i == 0){
			a[++cntDivisor] = i;
			if(x/i != i) a[++cntDivisor] = x/i;
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++)
		Divide(Read());
	sort(a+1, a+1+cntDivisor);
	int i = 1, j = a[1], used = 0;
	while(i<=cntDivisor && j<=n){
		int tot = 0;
		while(a[i] == j && j<=n){
			tot++;
			i++;
		}
		used++;
		ans[tot]++;
		j = a[i];
	}
	printf("%lld\n", n-used);
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}