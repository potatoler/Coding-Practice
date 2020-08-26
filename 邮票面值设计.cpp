#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2004;
int n, k, tmp[MaxN], value[MaxN], f[MaxN], ans;

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

inline int DP(int dep,int sum){
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	for(int i=1;i <=dep; i++)
		for(int j=tmp[i]; j<=n*sum; j++)
			f[j] = min(f[j], f[j-tmp[i]]+1);
	for(int i=1; i<=n*sum; i++)
		if(f[i] > n) return i-1;
	return n*sum;
}

inline void DFS(int dep,int lst1,int lst2,int sum){
	if(dep > k){
		if(ans < lst2){
			ans = lst2;
			for(int i=1; i<=k; i++)
				value[i] = tmp[i];
		}
		return ;
	}
	for(int i=lst1+1;i<=lst2+1;i++){
		tmp[dep] = i;
		int x = DP(dep, sum+i);
		DFS(dep+1, i, x, sum+i);
	}
}

signed main(){
	n = Read(), k = Read();
	DFS(1,0,0,0);
	for(int i=1; i<=k; i++)
		printf("%lld ", value[i]);
	printf("\n");
	printf("MAX=%lld\n", ans);
	return 0;
}