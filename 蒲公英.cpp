#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int N = 40040;
const int K = 220;
int n, m, L, len, sum[K][N], vis[N];
int tmpnum[N], B[N], last, pre[N];
struct getin {
	int id, d, se;
}a[N];
struct node {
	int num, s;
}p[K][K];
inline bool cmp1(getin x, getin y) { return x.d < y.d; }
inline bool cmp2(getin x, getin y) { return x.id < y.id; }
inline int getB(int x) {
	int ret = x / L;
	if(x % L) ret++;
	return ret;
}
inline void prework() {
	for(int i = 1; i <= len; i++) {
		memset(B, 0, sizeof(B)); node tmp;
		tmp.num = tmp.s = 0;
		for(int j = i; j <= len; j++) {
			for(int k = (j - 1) * L + 1; k <= min(n, j * L); k++) {
				B[a[k].se]++;
				if(B[a[k].se] > tmp.s) {
					tmp.num = a[k].se;
					tmp.s = B[a[k].se];
				}
				else if(B[a[k].se] == tmp.s)
					tmp.num = min(tmp.num, a[k].se), 
					tmp.s = B[a[k].se];
			}
			p[i][j] = tmp;
		}
	}
	for(int i = 1; i <= len; i++) {
		for(int j = 1; j <= n; j++) sum[i][a[j].se] = sum[i - 1][a[j].se];
		for(int j = (i - 1) * L + 1; j <= min(n, i * L); j++) 
			sum[i][a[j].se]++;
	}
}
signed main() {
	scanf("%lld%lld", &n, &m); L = sqrt(n);
	len = (n + L - 1) / L;
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i].d), a[i].id = i;
	sort(a + 1, a + n + 1, cmp1); a[0].d = -1;
	for(int i = 1; i <= n; i++) {
		a[i].se = a[i - 1].se;
		if(a[i - 1].d != a[i].d) 
			a[i].se++;
		pre[a[i].se] = a[i].d;
	}
	sort(a + 1, a + n + 1, cmp2);
	prework(); 
	for(int i = 1; i <= m; i++) {
		int l, r; scanf("%lld%lld", &l, &r);
		l = (l + last - 1) % n + 1;
		r = (r + last - 1) % n + 1;
		if(l > r) swap(l, r);
		int posl = getB(l), posr = getB(r);
		 if(posr - posl <= 2) {
			int ans = 0;
			for(int j = l; j <= r; j++) tmpnum[a[j].se] = 0;
			for(int j = l; j <= r; j++) {
				tmpnum[a[j].se]++;
				if(tmpnum[a[j].se] > tmpnum[ans]) ans = a[j].se;
				else if(tmpnum[a[j].se] == tmpnum[ans]) ans = min(ans, a[j].se);
			}
			printf("%lld\n", last = pre[ans]);
		} 
		else {
			int ans = p[posl + 1][posr - 1].num;
			tmpnum[ans] = 0, vis[ans] = 0;
			for(int j = l; j <= min(n, posl * L); j++) tmpnum[a[j].se] = 0, vis[a[j].se] = 0;
			for(int j = (posr - 1) * L + 1; j <= r; j++) tmpnum[a[j].se] = 0, vis[a[j].se] = 0;
			for(int j = l; j <= min(n, posl * L); j++) tmpnum[a[j].se]++;
			for(int j = (posr - 1) * L + 1; j <= r; j++) tmpnum[a[j].se]++;
			int MXnum, MX = 0;
			for(int j = l; j <= min(n, posl * L); j++)
				if(!vis[a[j].se]) {
					vis[a[j].se] = 1;
					int val = tmpnum[a[j].se] + sum[posr - 1][a[j].se] - sum[posl][a[j].se];
					if(MX < val)
						MX = val, 
						MXnum = a[j].se;
					else if(MX == val) MXnum = min(MXnum, a[j].se);
				}
			for(int j = (posr - 1) * L + 1; j <= r; j++)
				if(!vis[a[j].se]) {
					vis[a[j].se] = 1;
					int val = tmpnum[a[j].se] + sum[posr - 1][a[j].se] - sum[posl][a[j].se];
					if(MX < val)
						MX = val, 
						MXnum = a[j].se;
					else if(MX == val) MXnum = min(MXnum, a[j].se);
				}
			if(MX > tmpnum[ans] + p[posl + 1][posr - 1].s) ans = MXnum;
			else if(MX == tmpnum[ans] + p[posl + 1][posr - 1].s) ans = min(ans, MXnum);
			printf("%lld\n", last = pre[ans]);
		} 
	}
	return 0;
}