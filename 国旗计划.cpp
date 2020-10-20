#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m, cnt, f[MaxN*2][30], ans[MaxN], nxt[MaxN*2], fac[25];
struct Segment{
	int l, r, pos;
	bool operator < (const Segment &b) const{
		return l == b.l? r<b.r : l<b.l;
	}
}seg[MaxN*2];

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

inline int Get(int x){
	int l = 1, r = cnt+1, res = cnt+1;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(seg[mid].l <= x){
			l = mid+1;
			res = mid;
		}
		else r = mid-1;
	}
	return res;
}

inline int Query(int x){
	int res = 0, tmp = seg[x].l + m;
	for(int i=24; i>=0; i--)
		if(seg[f[x][i]].r < tmp){
			res += fac[i];
			x = nxt[f[x][i]];
		}
	return res;
}

signed main(){
	fac[0] = 1;
	for(int i=1; i<25; i++)
		fac[i] = fac[i-1] * 2;
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int l = Read(), r = Read();
		if(r < l) seg[++cnt] = (Segment){l, r+m, i};
		else{
			seg[++cnt] = (Segment){l, r, i};
			seg[++cnt] = (Segment){l+m, r+m, i};
		}
	}
	sort(seg+1, seg+1+cnt);
	seg[cnt+1].r = 2000000000;
	for(int i=1; i<=cnt+1; i++)
		for(int j=0; j<25; j++)
			f[i][j] = cnt+1;
	for(int i=1; i<=cnt; i++){
		f[i][0] = i;
		nxt[i] = Get(seg[i].r);
	}
	nxt[cnt+1] = cnt+1;
	for(int j=1; j<25; j++)
		for(int i=1; i<=cnt; i++)
			f[i][j] = f[nxt[f[i][j-1]]][j-1];
	for(int i=1; i<=cnt; i++)
		if(!ans[seg[i].pos]) ans[seg[i].pos] = Query(i)+1;
	for(int i=1; i<=n; i++)
		printf("%lld ", ans[i]);
	return 0;
}