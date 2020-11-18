#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 24;
int n, m, fri[MaxN], f[1<<MaxN], last[1<<MaxN], used[1<<MaxN];
int stack[MaxN], top;

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
//	freopen("party.in", "r", stdin);
//	freopen("party.out", "w", stdout);
	n = Read(), m = Read();
//	if(m == n * (n-1) / 2){
//		printf("0");
//		return 0;
//	}
	for(int i=1; i<=m; i++){
		int u = Read()-1, v = Read()-1;
		fri[u] |= (1<<v);
		fri[v] |= (1<<u);
	}
	for(int i=0; i<n; i++)
		fri[i] |= (1<<i);
	memset(f, 0x3f, sizeof(f));
	for(int i=0; i<n; i++){
		f[fri[i]] = 1;
		used[fri[i]] = i;
	}
	for(int s=0; s<(1<<n); s++){
		for(int i=0; i<n; i++){
			if((s & (1<<i)) && (f[s|fri[i]] > f[s]+1)){
				f[s|fri[i]] = f[s]+1;
				last[s|fri[i]] = s;
				used[s|fri[i]] = i;
			}
		}
	}
	printf("%lld\n", f[(1<<n)-1]);
	for(int i=(1<<n)-1; i; i = last[i])
		stack[++top] = used[i]+1;
	sort(stack+1, stack+1+top);
	for(int i=1; i<=top; i++)
		printf("%lld ", stack[i]);
	return 0;
}