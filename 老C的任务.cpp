#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100010;

#define rep(i,l,r) for (int i=l; i<=r; i++)
#define find(x) lower_bound(b+1,b+tot+1,x)-b

int n, m, tot, cnt, x[MaxN], y[MaxN], x_1[MaxN], y_1[MaxN], x_2[MaxN], y_2[MaxN], b[MaxN << 3], p[MaxN], c[MaxN << 3], ans[MaxN];

struct P{
	int x, y, p; 
}pt[MaxN << 1];

struct Q{
	int x, l, r, pos;
}q[MaxN << 1];

bool operator <(P a,P b){
	return a.x<b.x;
}

bool operator <(Q a,Q b){
	return a.x<b.x;
}

inline void add(int x, int k){ for (; x<=tot; x+=x&-x) c[x]+=k; }

inline int que(int x){
	int res=0;
	for (; x; x-=x&-x)
		res+=c[x];
	return res;
}

signed main(){
	scanf("%lld%lld",&n,&m);
	rep(i,1,n) scanf("%lld%lld%lld",&x[i],&y[i],&p[i]),b[++tot]=x[i],b[++tot]=y[i];
	rep(i,1,m){
		scanf("%lld%lld%lld%lld",&x_1[i],&y_1[i],&x_2[i],&y_2[i]);
		b[++tot]=x_1[i]-1; b[++tot]=y_1[i]-1; b[++tot]=x_2[i]; b[++tot]=y_2[i];
	}
	sort(b+1,b+tot+1); tot=unique(b+1,b+tot+1)-b-1;
	rep(i,1,n) x[i]=find(x[i]),y[i]=find(y[i]),pt[i]=(P){x[i],y[i],p[i]};
	rep(i,1,m){
		x_1[i]=find(x_1[i]-1); y_1[i]=find(y_1[i]-1);
		x_2[i]=find(x_2[i]); y_2[i]=find(y_2[i]);
		q[++cnt]=(Q){x_1[i],y_1[i],y_2[i],i}; q[++cnt]=(Q){x_2[i],y_1[i],y_2[i],i};
	}
	sort(pt+1,pt+n+1); sort(q+1,q+cnt+1); int now=1;
	rep(i,1,cnt){
		while (pt[now].x<=q[i].x && now<=n) add(pt[now].y,pt[now].p),now++;
		if (!ans[q[i].pos]) ans[q[i].pos]=que(q[i].r)-que(q[i].l);
			else ans[q[i].pos]=que(q[i].r)-que(q[i].l)-ans[q[i].pos];
	}
	rep(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}