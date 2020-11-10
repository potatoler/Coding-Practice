#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 500005;
int f[MaxN], n, q, a[MaxN], b[MaxN], ans[MaxN];
bool visited[MaxN];

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
		a[i] = Read(), b[i] = Read();
	q = Read();
	while(q--){
		int k = Read(), m = Read();
		if(visited[k]){
			printf("%lld\n", ans[k]);
			continue;
		}
		visited[k] = true;
		for(int i=1; i<=n; i++)
			f[i] = -INT_MAX;
		f[0] = 0;
		for(int i=1; i<=n; i++)
			for(int j=min(i,m); j>=1; j--)
				f[j] = max(f[j], f[j-1] + (a[i] * k + b[i]));
		ans[k] = f[m];
		printf("%lld\n", ans[k]);
	}
}