#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, mx[MaxN][3], mn[MaxN][3], cnt, son[MaxN][2];
char str[MaxN];

inline int Build(){
	int cur = ++cnt;
	if(str[cur] == '2'){
		son[cur][0] = Build();
		son[cur][1] = Build();
	}
	else if(str[cur] == '1') son[cur][0] = Build();
	return cur;
}

inline void DFS(int x){
	int l = son[x][0], r = son[x][1];
	if(l) DFS(l);
	if(r) DFS(r);
	if(!l){
		mx[x][0] = mn[x][0] = 1;
		mx[x][1] = mx[x][2] = mn[x][1] = mn[x][2] = 0;
	}
	mx[x][0] = max(mx[l][1]+mx[r][2], mx[l][2]+mx[r][1]) + 1;
	mx[x][1] = max(mx[l][0]+mx[r][2], mx[l][2]+mx[r][0]);
	mx[x][2] = max(mx[l][0]+mx[r][1], mx[l][1]+mx[r][0]);
	mn[x][0] = min(mn[l][1]+mn[r][2], mn[l][2]+mn[r][1]) + 1;
	mn[x][1] = min(mn[l][0]+mn[r][2], mn[l][2]+mn[r][0]);
	mn[x][2] = min(mn[l][0]+mn[r][1], mn[l][1]+mn[r][0]);
	return;
}

signed main(){
	scanf("%s", str+1);
	n = strlen(str) - 1;
	int root = Build();
	DFS(root);
	int maxans = max(mx[1][0], max(mx[1][1], mx[1][2])), minans = min(mn[1][0], min(mn[1][1], mn[1][2]));
	printf("%lld %lld", maxans, minans);
	return 0;
}