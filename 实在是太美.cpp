#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, a[MaxN], b[MaxN], ans = LLONG_MAX, sum;
int str[MaxN];

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

inline bool Judge(){
	int num = 0;
	for(int i=1; i<=n; i++){
		if(str[i] == 1) num++;
		if(str[i] == 2) num--;
		if(num < 0) return false;
	}
	if(num == 0) return true;
	return false;
}

inline void DFS(int len){
	if(len == n+1){
//		for(int i=1; i<len; i++)
//			printf("%lld", str[i]);
//		printf(" %lld\n", sum);
		if(Judge()) ans = min(ans, sum);
		return;
	}
	str[len] = 1, sum += a[len];
	DFS(len+1);
	sum -= a[len];
	str[len] = 2, sum += b[len];
	DFS(len+1);
	sum -= b[len];
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++)
		b[i] = Read();
	DFS(1);
	printf("%lld", ans);
	return 0;
}