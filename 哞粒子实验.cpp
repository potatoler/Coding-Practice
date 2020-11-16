#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, pre[MaxN], suf[MaxN], ans;
pair<int,int> pos[MaxN];

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
//	freopen("moop.in", "r", stdin);
//	freopen("moop.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++){
		int x = Read(), y = Read();
		pos[i] = make_pair(x,y);
	}
	sort(pos+1, pos+1+n);
	pre[0] = INT_MAX, suf[n+1] = -INT_MAX;
	for(int i=1; i<=n; i++)
		pre[i] = min(pre[i-1], pos[i].second);
	for(int i=n; i>=1; i--)
		suf[i] = max(suf[i+1], pos[i].second);
	for(int i=1; i<=n; i++)
		if(pre[i] > suf[i+1]) ans++;
	printf("%lld", ans);
	return 0;
}