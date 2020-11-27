#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 300005, Mod = 998244353;
int n, x, a[MaxN], ans;
class Trie{
	private:
	int idx[MaxN*60][2], sum[MaxN*60], root, cnt;
	
	public:
	inline int Find(int pos){
		int res = 0;
		root = 0;
		for(int i=60; i>=0; i--){
			if(x & (1ll<<i)){
				if(pos & (1ll<<i)) root = idx[root][0];
				else root = idx[root][1];
			}
			else{
				if(pos & (1ll<<i)){
					if(idx[root][0]) res = (res + sum[idx[root][0]]) % Mod;
					root = idx[root][1];
				}
				else{
					if(idx[root][1]) res = (res + sum[idx[root][1]]) % Mod;
					root = idx[root][0];
				}
			}
			if(!root) break;
		}
		if(root) res = (res + sum[root]) % Mod;
		return res;
	}
	
	inline void Insert(int pos, int val){
		root = 0;
		for(int i=60; i>=0; i--){
			if(pos & (1ll<<i)){
				if(!idx[root][1]){
					idx[root][1] = ++cnt;
					sum[root] = (sum[root] + val) % Mod;
					root = cnt;
				}
				else{
					sum[root] = (sum[root] + val) % Mod;
					root = idx[root][1];
				}
			}
			else{
				if(!idx[root][0]){
					idx[root][0] = ++cnt;
					sum[root] = (sum[root] + val) % Mod;
					root = cnt;
				}
				else{
					sum[root] = (sum[root] + val);
					root = idx[root][0];
				}
			}
		}
		sum[root] = (sum[root] + val) % Mod;
		return;
	}
}trie;

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
	n = Read(), x = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	sort(a+1, a+1+n);
	for(int i=n; i; i--){
		int tmp = (trie.Find(a[i]) + 1) % Mod;
		ans = (ans + tmp) % Mod;
		trie.Insert(a[i], tmp);
	}
	printf("%lld", ans);
	return 0;
}