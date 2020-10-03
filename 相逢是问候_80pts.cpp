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
const int MaxN = 51000;
int n, m, p, c, phi[60], a[MaxN], prime[MaxN], tms;
bool notPrime[MaxN], flag;
struct SegmentTree{
	int l, r, sum, cnt;
}tree[MaxN * 4];

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

inline void Write(int x){
	if(x<0) putchar('-'), x=-x;
	if(x>9) Write(x/10);
	putchar(x%10+'0');
	return;
}

inline int Phi(int x){
	int ans = x;
	for(int i=1; i<=prime[0] && prime[i] * prime[i] <= x; i++){
		if(x % prime[i] == 0) ans = ans * (prime[i]-1)/prime[i];
		while(x % prime[i] == 0) x = x / prime[i];
	}
	if(x>1) ans = ans / x * (x-1);
	return ans;
}

inline void Eular(){
	for(int i=2; i<=10004; i++){
		if(!notPrime[i]) prime[++prime[0]] = i;
		for(int j=1; j<=prime[0]; j++){
			if(i * prime[j] > 10004) break;
			notPrime[i*prime[j]] = true;
			if(i % prime[j] == 0) break;
		}
	}
	phi[tms] = p;
	while(phi[tms] != 1){
		tms++;
		phi[tms] = Phi(phi[tms-1]);
	}
	tms++;
	phi[tms] = 1;
}

inline int QuickPower(int y, int mod){
	int ans = 1, x = c;
	while(y){
		if(y & 1) ans *= x;
		x *= x;
		y >>= 1;
		if(ans >= mod){
			flag = true;
			ans %= mod;
		}
		if(x >= mod){
			flag = true;
			x %= mod;
		}
	}
	return ans % mod;
}

inline int Work(int a, int t){
	int tmp = a;
	if(tmp > phi[t]) tmp = tmp % phi[t] + phi[t];
	for(int i=t; i>0; i--){
		flag = false;
		tmp = QuickPower(tmp, phi[i-1]);
		if(flag){
			tmp += phi[i-1];
			flag = false;
		}
	}
	return tmp;
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	return;
}

inline void Change(int x, int l, int r){
	if(tree[x].cnt >= tms) return;
	if(tree[x].l == tree[x].r){
		tree[x].cnt++;
		tree[x].sum = Work(a[tree[x].l], tree[x].cnt) % p;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(mid >= r) Change(x*2, l, r);
	else if(l > mid) Change(x*2+1, l, r);
	else{
		Change(x*2, l, mid);
		Change(x*2+1, mid+1, r);
	}
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].cnt = min(tree[x*2].cnt, tree[x*2+1].cnt);
}

inline int Query(int x, int l, int r){
	if(tree[x].l == l && tree[x].r == r) return tree[x].sum;
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(mid >= r) return Query(x*2, l, r);
	else if(l > mid) return Query(x*2+1, l, r);
	else return (Query(x*2, l, mid) + Query(x*2+1, mid+1, r)) % p;
}

signed main(){
	n = Read(), m = Read(), p = Read(), c = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	Eular();
	Build(1, 1, n);
	while(m--){
		int op = Read(), l = Read(), r = Read();
		if(op == 0) Change(1, l, r);
		else{
			Write(Query(1, l, r) % p);
			putchar('\n');
		}
	}
	return 0;
}