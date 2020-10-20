#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 5003, MaxM = 300005;
int n, m, k, a[MaxN], b[MaxN], c[MaxN], latest[MaxN], f[MaxN][MaxN];
pair<int, int> castle[MaxN];

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
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read(), b[i] = Read(), c[i] = Read();
		latest[i] = i;
	}
	while(m--){
		int u = Read(), v = Read();
		latest[v] = max(latest[v], u);
	}
	for(int i=1; i<=n; i++)
		castle[i] = make_pair(latest[i], c[i]);
	sort(castle+1, castle+1+n);
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld\n", castle[i].first, castle[i].second);
	for(int i=0; i<=k; i++)
		f[0][i] = 0;
	for(int i=k+1; i<=5000; i++)
		f[0][i] = -INT_MAX;
	int p = 1;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=5000; j++)
			f[i][j] = -INT_MAX;
		for(int j=a[i]; j<=5000-b[i]; j++)
			f[i][j+b[i]] = max(f[i][j+b[i]], f[i-1][j]);
		while(p<=n && castle[p].first == i){
			for(int j=0; j<5000; j++)
				f[i][j] = max(f[i][j], f[i][j+1] + castle[p].second);
			p++;
		}
	}
	int ans = -1;
	for(int i=0; i<=5000; i++)
		ans = max(ans, f[n][i]);
	printf("%lld", ans);
	return 0;
}