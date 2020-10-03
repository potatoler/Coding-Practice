#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 500005, MaxLog = 55, MaxP = 10000;
int n, m, p, c;
int a[MaxN], phi[MaxN], maxTimes, power[MaxP+1][MaxLog][2];
bool flag, over[MaxP+1][MaxLog][2];
struct SegmentTree{
	int l, r, sum, tms;
}tree[MaxN*4];

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


inline int Phi(int x){
	int ans = x;
	for(int i = 2; i*i<=x; i++){
		if(x % i == 0)
			ans = ans / i * (i-1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) ans = ans / x * (x-1);
	return ans;
}   

inline void Init(){
	int x = p;
	phi[0] = x;
	while(x>1){
		x = Phi(x);
		phi[++maxTimes]=x;
	}
	phi[++maxTimes] = 1;
	for(int i=0; i<=maxTimes; i++){
		power[0][i][0] = 1;
		for(int j=1; j<=MaxP; j++){
			power[j][i][0] = power[j-1][i][0] * c;
			if(power[j][i][0] >= phi[i]){
				over[j][i][0] = true;
				power[j][i][0] %= phi[i];
			}
			over[j][i][0] |= over[j-1][i][0];
		}
	}
	for(int i=0; i<=maxTimes; i++){
		power[0][i][1] = 1;
		for(int j=1; j<=MaxP; j++){
			power[j][i][1] = power[j-1][i][1] * power[MaxP][i][0];
			if(power[j][i][1] >= phi[i]){
				over[j][i][1] = true;
				power[j][i][1] %= phi[i];
			}
			over[j][i][1] |= over[j-1][i][1];
		}
	}
}

inline int QuickPower(int ind, int p){
	flag |= over[ind % MaxP][p][0] | over[ind / MaxP][p][1];
	int ans = power[ind % MaxP][p][0] * power[ind / MaxP][p][1];
	if(ans >= phi[p]){
		flag = true;
		ans %= phi[p];
	}
	return ans;
}

inline int Calculate(int id, int limit,int tms){
	flag = false;
	if(tms == limit){
		if(a[id] >= phi[tms]){
			flag = true;
			return a[id] % phi[tms];
		}
		return a[id];
	}
	int x = Calculate(id, limit, tms+1);
	if(flag){
		x += phi[tms+1];
		flag=false;
	}
	return QuickPower(x, tms);
}

inline void Update(int x){
	tree[x].sum = (tree[x*2].sum + tree[x*2+1].sum) % p;
	tree[x].tms = min(tree[x*2].tms, tree[x*2+1].tms);
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].sum = a[l];
		tree[x].tms = 0;
		return;
	}
	int mid = (l+r) >> 1;
	Build(x*2, l, mid), Build(x*2+1, mid+1, r);
	Update(x);
	return;
}

inline void Change(int x, int l, int r){
	if(tree[x].tms >= maxTimes) return;
	if(tree[x].l == tree[x].r){
		tree[x].tms++;
		tree[x].sum = Calculate(tree[x].l, tree[x].tms, 0);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(l <= mid) Change(x*2, l, r);
	if(r > mid) Change(x*2+1, l, r);
	Update(x);
}

inline int Query(int x, int l, int r){
	if(l <= tree[x].l&& tree[x].r <= r) return tree[x].sum;
	int mid = (tree[x].l + tree[x].r) >> 1;
	int ans = 0;
	if(l <= mid) ans += Query(x*2, l, r);
	if(r > mid) ans += Query(x*2+1, l, r);
	ans %= p;
	return ans;
}

signed main(){
	n = Read(), m = Read(), p = Read(), c = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	Init();
	Build(1,1,n);
	while(m--){
		int op = Read(), l = Read(), r = Read();
		if(op == 0) Change(1, l, r);
		else printf("%lld\n", Query(1, l, r));
	}
	return 0;
}