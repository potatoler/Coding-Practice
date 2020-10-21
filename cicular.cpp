#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, ans, stack[MaxN*2], top, father[MaxN*2][20], cntSegment, cntUncover;
bool cover[MaxN*2];
struct Segment{
	int l, r;
	bool operator < (const Segment &y) const{
		return l < y.l || (l == y.l && r > y.r);
	}
}seg[MaxN*2], unc[MaxN*2];

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

inline bool Check(int nums, int x){
	int stl = unc[x].l;
	for(int i=0; (1<<i)<=nums; i++){
		if(nums>>i&1) x = father[x][i];
	}
	if(!x) return false;
	return stl+m >= unc[x].r;
}

signed main(){
//	freopen("c.in", "r", stdin);
//	freopen("c.out", "w", stdout);
	m = Read(), n = Read();
	for(int i=1; i<=n; i++){
		int l = Read(), r = Read();
		if(l > r) r += m;
		seg[++cntSegment] = (Segment){l,r};
		seg[++cntSegment] = (Segment){l+m, r+m};
	}
	sort(seg+1, seg+1+cntSegment);
	for(int i=1; i<=cntSegment; i++){
		while(top && seg[stack[top]].r >= seg[i].r){
			cover[stack[top--]] = true;
		}
		stack[++top]= i;
	}
	for(int i=1; i<=cntSegment; i++){
		if(!cover[i]){
			unc[++cntUncover] = seg[i];
		}
	}
//	exit(0);
	int p=1;
	for(int i=1; i<=cntUncover; i++){
		while(unc[p].l < unc[i].r && p <= cntUncover) p++;
		if(p > cntUncover) break;
		father[i][0] = p;
	}
//	exit(0);
	for(int j=1; (1<<j)<=cntUncover; j++){
		for(int i=1; i<=cntUncover; i++){
			father[i][j] = father[father[i][j-1]][j-1];
		}
	}
//	exit(0);
	for(int i=1; i<=cntUncover; i++){
		int l=0, r=n-1;
		while(l < r){
			int mid = (l+r+1) >> 1;
			if(Check(mid, i)) l = mid;
			else r = mid-1;
		}
		ans = max(ans, r+1);
	}
	printf("%lld", ans);
	return 0;
}