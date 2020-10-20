#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005, MaxLog = 21, Mod = 1000000007;
int n, m, cnt, belong[MaxN*MaxLog], father[MaxN][MaxLog], ls[MaxN*MaxLog], rs[MaxN*MaxLog], lg[MaxN], uni, ans = 9;

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
	if(belong[x] == x) return x;
	return belong[x] = Find(belong[x]);
}

inline void Merge(int x, int y){
	int xbelong = Find(x), ybelong = Find(y);
	if(xbelong != ybelong) belong[ybelong] = xbelong;
	return;
}

signed main(){
	uni = n = Read(), m = Read();
	for(int i=2; i<=n; i++)
		lg[i] = lg[i>>1] + 1;
	for(int j=lg[n]; j>=0; j--){
		for(int i=1; i+(1<<j)-1 <= n; i++){
			cnt++;
			father[i][j] = cnt;
			belong[cnt] = cnt;
		}
	}
	for(int j=1; j<=lg[n]; j++){
		for(int i=1; i+(1<<j)-1 <= n; i++){
			ls[father[i][j]] = father[i][j-1];
			rs[father[i][j]] = father[i+(1<<(j-1))][j-1];
		}
	}
	for(int i=1; i<=m; i++){
		int l1 = Read(), r1 = Read(), l2 = Read(), r2 = Read();
		int k = lg[r1-l1+1];
		Merge(father[l1][k], father[l2][k]);
		Merge(father[r1-(1<<k)+1][k], father[r2-(1<<k)+1][k]);
	}
	for(int i=1; i<=cnt; i++){
		if(!ls[i] || !rs[i]) continue;
		int ibelong = Find(i);
		if(ibelong != i){
			Merge(ls[ibelong], ls[i]);
			Merge(rs[ibelong], rs[i]);
		}
	}
	for(int i=1; i<=n; i++)
		if(Find(father[i][0]) != father[i][0]) uni--;
	for(int i=1; i<uni; i++)
		ans = ans % Mod * 10 % Mod;
	printf("%lld", ans);
	return 0;
}