#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, m, a[MaxN];

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
	n = Read(), m = Read();
	int sum = 0;
	for(int i=1; i<=n; i++){
		a[i] = Read();
		sum += a[i];
	}
	printf("%lld", sum);
	return 0;
}