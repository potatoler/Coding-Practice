#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;
const int MaxN = 500005;
typedef long long ll;
struct Block{
	ll distance, value;
}block[MaxN];
ll f[MaxN], deque[MaxN], sum, ans;
ll n, d, k, lside, rside;

ll DP(int l, int r){
	for(int i=1;i<MaxN;i++)
		f[i] = -INT_MAX;
	f[0] = 0;
	memset(deque, 0, sizeof(deque));
	int head = 1, tail = 0, p = 0;
	for(int i=1;i<=n;i++){
		while(block[i].distance - block[p].distance >= l && p < i){
			if(f[p] != -INT_MAX){
				while(head <= tail && f[deque[tail]] <= f[p])
					tail--;
				deque[++tail] = p;
			}
			p++;
		}
		while(head <= tail && block[i].distance - block[deque[head]].distance > r)
			head++;
		if(head <= tail)
			f[i] = f[deque[head]] + block[i].value;
	}
	ll res = -INT_MAX;
	for(int i=1;i<=n;i++)
		res = max(res, f[i]);
	return res;
}

int main(){
	scanf("%lld%lld%lld",&n,&d,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld", &block[i].distance, &block[i].value);
		if(block[i].value > 0)
			sum += block[i].value;
	}
	rside = max(block[n].distance, d);
	if(sum < k){
		printf("-1");
		return 0;
	}
	while(lside <= rside){
		int mid = (lside + rside) / 2;
		int l = max((ll)1, d-mid), r = d+mid;
		ll val = DP(l, r);
		if(val < k) lside = mid + 1;
		else{
			ans = mid;
			rside = mid-1;
		}
	}
	printf("%lld",ans);
	return 0;
}