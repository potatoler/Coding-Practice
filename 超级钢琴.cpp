#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, k, L, R, ans, sum[MaxN], st[MaxN][30];
struct QuadPair{
	int x, l, r, t;
	bool operator < (const QuadPair &y) const {
		return sum[t] - sum[x-1] < sum[y.t] - sum[y.x-1];
	}
};
priority_queue<QuadPair> q;

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

inline void Init(){
	for(int i=1; i<=n; i++)
		st[i][0] = i;
	int t = (int)log2(n);
	for(int j=1; j<=t; j++){
		for(int i=1; i+(1<<j)-1<=n; i++){
			int x = st[i][j-1], y = st[i+(1<<(j-1))][j-1];
			st[i][j] = sum[x] > sum[y] ? x : y;
		}
	}
	return;
}

inline int Query(int l, int r){
	int t = (int)log2(r-l+1), x = st[l][t], y = st[r-(1<<t)+1][t];
	return sum[x] > sum[y] ? x : y;
}

signed main(){
	n = Read(), k = Read(), L = Read(), R = Read();
	for(int i=1; i<=n; i++)
		sum[i] = Read(), sum[i] += sum[i-1];
//	for(int i=1; i<=n; i++)
//		printf("%lld ",sum[i]);
	Init();
	for(int i=1; i<=n; i++)
		if(i+L-1 <= n) q.push((QuadPair){i, i+L-1, min(n,i+R-1), Query(i+L-1, min(n, i+R-1))});
	while(k--){
		int x = q.top().x, l = q.top().l, r = q.top().r, t = q.top().t;
		q.pop();
		ans += sum[t] - sum[x-1];
		if(l != t) q.push((QuadPair){x, l, t-1, Query(l, t-1)});
		if(r != t) q.push((QuadPair){x, t+1, r, Query(t+1, r)});
	}
	printf("%lld", ans);
	return 0;
}