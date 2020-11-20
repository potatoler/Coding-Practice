#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
int n;
struct Segment{
	int l, r;
	bool operator < (const Segment &y) const{
		return r == y.r? l < y.l : r < y.r;
	}
}seg[MaxN];

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
	n = Read();
	for(int i=1; i<=n; i++){
		int x = Read(), w = Read();
		seg[i].l = x-w, seg[i].r = x+w;
	}
	sort(seg+1, seg+1+n);
	int ans = 0, last = -INT_MAX;
	for(int i=1; i<=n; i++){
		if(last <= seg[i].l){
			ans++;
			last = seg[i].r;
		}
	}
	printf("%lld", ans);
	return 0;
}