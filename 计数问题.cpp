#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
int n, m, q, value[305][305], tree[105][305][305];

inline int Lowbit(int x){
	return x & -x;
}

inline void Add(int val, int x, int y, int w){
	value[x][y] = val;
	for(int i=x; i<=n; i+=Lowbit(i))
		for(int j=y; j<=m; j+=Lowbit(j))
			tree[val][i][j] += w;
}

inline int Sum(int val, int x, int y){
	int ans = 0;
	for(int i=x; i; i-=Lowbit(i))
		for(int j=y; j; j-=Lowbit(j))
			 ans += tree[val][i][j];
	return ans;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			scanf("%lld", &x);
			Add(x, i, j, 1);
		}
	}
	scanf("%lld", &q);
	for(int i=1;i<=q;i++){
		int op;
		scanf("%lld", &op);
		if(op == 1){
			int x, y, val;
			scanf("%lld%lld%lld", &x, &y, &val);
			Add(value[x][y], x, y ,-1);
			Add(val, x, y, 1);
		}
		else{
			int x1, x2, y1, y2, val;
			scanf("%lld%lld%lld%lld%lld", &x1, &x2, &y1, &y2, &val);
			printf("%lld\n", Sum(val, x2, y2) - Sum(val, x1-1, y2) - Sum(val, x2, y1-1) + Sum(val, x1-1, y1-1));
		}
	}
	return 0;
}