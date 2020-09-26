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
int n, ans, a[MaxN], l[MaxN], r[MaxN];

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
	int p = 0, q = 0;
	for(int i=1; i<=n+1; i++){
		while(a[i] > p){
			p++, ans++;
			l[ans] = i;
		}
		while(a[i] < p){
			p--, q++;
			r[q] = i-1;
		}
	}
	printf("%lld\n", ans);
	for(int i=1; i<=ans; i++)
		printf("%lld %lld\n", l[i], r[i]);
	return 0;
}