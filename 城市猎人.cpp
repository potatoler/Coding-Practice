#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
int n, m, q;
int father[MaxN], depth[MaxN], level[MaxN], minTime[MaxN];

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

inline int Find(int x){
	if(father[x] == x) return x;
	return Find(father[x]);
}

inline void Update(int x){
	if(father[x] == x) return;
	Update(father[x]);
	depth[x] = depth[father[x]] + 1;
}

inline int Query(int a, int b){
	int ans = 0;
	if(depth[a] < depth[b]) swap(a,b);
	while(depth[a] > depth[b]){
		ans = max(ans, minTime[a]);
		a = father[a];
	}
	while(a != b){
		ans = max(ans, max(minTime[a], minTime[b]));
		a = father[a];
		b = father[b];
	}
	return ans;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=n; i++){
		father[i] = i;
		level[i] = 1;
	}
	for(int i=1; i<=m; i++){
		int gcd = m-i+1, r = n / gcd;
		for(int j=2; j<=r; j++){
			int f1 = Find(gcd*(j-1)), f2 = Find(gcd*j);
			if(f1 != f2){
				if(level[f1] < level[f2]) swap(f1, f2);
				father[f2] = f1;
				minTime[f2] = i;
				level[f1] = max(level[f1], level[f2]+1);
			}
		}
	}
	for(int i=1; i<=n; i++)
		Update(i);
	for(int i=1; i<=q; i++){
		int x = Read(), y = Read();
		printf("%d\n", Query(x, y));
	}
	return 0;
}