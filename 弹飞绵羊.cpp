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
int n, m, len, k[MaxN], f[MaxN], to[MaxN], block[MaxN], side[MaxN];

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

inline void Change(int pos, int val){
	k[pos] = val;
	for(int i = side[block[pos]+1]-1; i>=side[block[pos]]; i--){
		if(i + k[i] >= side[block[i]+1]){
			f[i] = 1;
			to[i] = i + k[i];
		}
		else{
			f[i] = f[i+k[i]] + 1;
			to[i] = to[i+k[i]];
		}
	}
	return;
}

inline int Query(int pos){
	int ans = 0;
	while(pos <= n){
		ans += f[pos];
		pos = to[pos];
	}
	return ans;
}

signed main(){
	n = Read();
	len = sqrt(n);
	for(int i=1; i<=n; i++){
		k[i] = Read();
		block[i] = (i-1) / len + 1;
		if(block[i] != block[i-1]) side[block[i]] = i;
	}
	side[block[n]+1] = n+1;
	for(int i=n; i>=1; i--){
		if(i+k[i] >= side[block[i]+1]){
			f[i] = 1;
			to[i] = i + k[i];
		}
		else{
			f[i] = f[i+k[i]] + 1;
			to[i] = to[i+k[i]];
		}
	}
	m = Read();
	while(m--){
		int op = Read();
		if(op == 1){
			int j = Read();
			printf("%lld\n", Query(j+1));
		}
		else{
			int j = Read(), newk = Read();
			Change(j+1, newk);
		}
	}
	return 0;
}