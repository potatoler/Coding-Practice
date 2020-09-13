#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 5003;
int n, a[MaxN], f[MaxN], g[MaxN], ans, ways;

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
	f[1] = 1;
	ans = 1;
	for(int i=1; i<=n; i++){
		f[i] = 1;
		for(int j=1; j<i; j++){
			if(a[j] > a[i]){
				f[i] = max(f[i], f[j]+1);
				ans = max(ans, f[i]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(f[i] == 1) g[i] = 1;
		for(int j=1; j<i; j++){
			if(a[j] > a[i] && f[i] == f[j]+1) g[i] += g[j];
			else if(a[i] == a[j] && f[i] == f[j]) g[i] = 0;
		}
	}
	for(int i=1; i<=n; i++)
		if(f[i] == ans) ways += g[i];
	printf("%d %d", ans, ways);
	return 0;
}