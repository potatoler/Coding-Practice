#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N = 200005;
int n,m,c[N],dp[N];
struct node { int l,r,w; } a[N];
bool operator <(node a,node b) { return a.r<b.r; }

#define ls (o<<1)
#define rs (o<<1|1)

int maxv[N<<2],addv[N<<2];
inline void update(int o,int w) { addv[o]+=w,maxv[o]+=w; }
inline void pushup(int o) { maxv[o]=max(maxv[ls],maxv[rs]); }
inline void pushdown(int o) {
	if (addv[o]) update(ls,addv[o]),update(rs,addv[o]),addv[o]=0;
}
inline void modify(int o,int l,int r,int ql,int qr,int w) {
	if (ql<=l&&r<=qr) { update(o,w); return; }
	int mid=(l+r)>>1; pushdown(o);
	if (ql<=mid) modify(ls,l,mid,ql,qr,w);
	if (qr>mid) modify(rs,mid+1,r,ql,qr,w);
	pushup(o);
}
inline int query(int o,int l,int r,int ql,int qr) {
	if (ql<=l&&r<=qr) return maxv[o];
	int mid=(l+r)>>1;
	int res=0; pushdown(o);
	if (ql<=mid) res=max(res,query(ls,l,mid,ql,qr));
	if (qr>mid) res=max(res,query(rs,mid+1,r,ql,qr));
	pushup(o); return res;
}

signed main() {
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=n;++i) scanf("%lld",&c[i]);
	for (int i=1;i<=m;++i) scanf("%lld%lld%lld",&a[i].l,&a[i].r,&a[i].w);
	sort(a+1,a+m+1);
	for (int i=1,p=1;i<=n;++i) {
		while (p<=m&&a[p].r<=i) modify(1,0,n,0,a[p].l-1,a[p].w),++p;
		modify(1,0,n,0,i-1,-c[i]);
		dp[i]=max(dp[i-1],query(1,0,n,0,i-1));
		modify(1,0,n,i,i,dp[i]);
	}
	printf("%lld\n",dp[n]);
	return 0;
}