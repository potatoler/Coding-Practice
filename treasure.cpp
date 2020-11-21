#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int MaxN = 300005, MaxM = 1000006;
int n, T, Q, ans[MaxN], mx;
struct Treasure{
	int t, w;
	bool operator < (const Treasure &y) const {
		return w < y.w;
	}
}tr[MaxN];

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

class BinaryIndexedTree{
	private:
	int value[MaxM], sum[MaxM];
	
	public:
	inline void Add(int pos, int w){
		int i = pos;
		while(i <= mx){
			value[i] += w;
			sum[i] += pos * w;
			i += lowbit(i);
		}
		return;
	}
	
	inline int Ask(int pos){
		int cur = 0, res = 0;
		if(pos == 0) return 0;
		for(int i = 19; i>=0; i--){
			if(cur+(1<<i) <= mx && value[cur+(1<<i)] < pos){
				pos -= value[cur+(1<<i)];
				res += sum[cur+(1<<i)];
				cur += (1<<i);
			}
		}
		return res + (cur+1) * pos;
	}
}pre, suf;

signed main(){
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	n = Read(), T = Read(), Q = Read();
	for(int i=1; i<=n; i++){
		tr[i].w = Read(), tr[i].t = Read();
		mx = max(mx, tr[i].t+1);
	}
	sort(tr+1, tr+1+n);
	for(int i=1; i<n; i++)
		pre.Add(tr[i].t+1, 1);
	for(int i=n; i; i--){
		int l = 1, r = min(n-i, i-1), res = 0;
		if(tr[i].t > T){
			if(i != 1){
				pre.Add(tr[i-1].t+1, -1);
				suf.Add(tr[i-1].t+1, 1);
				continue;
			}
		}
		while(l <= r){
			int mid = (l+r) >> 1;
			if(pre.Ask(mid)-mid + suf.Ask(mid)-mid + tr[i].t <= T){
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		if(!ans[res]) ans[res] = tr[i].w + 1;
		if(i != 1){
			pre.Add(tr[i-1].t+1, -1);
			suf.Add(tr[i].t+1, 1);
		}
	}
	for(int i=n/2; i>=0; i--)
		ans[i] = max(ans[i], ans[i+1]);
	while(Q--){
		int x = Read();
		x /= 2;
		if(!ans[x]) printf("-1\n");
		else printf("%lld\n", ans[x]-1);
	}
	return 0;
}