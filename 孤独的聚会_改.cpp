#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
int n, m, cnt, ans[30], f[30], s[30], seq[30], sum, cur;

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

inline void DFS(int x, int f[30]){
	if(cur > cnt) return;
	int flag = true;
	for(int i=1; i<=n; i++){
		if(f[i] != sum){
			flag = false;
			break;
		}
	}
	if(flag){
		cnt = cur;
		for(int i=1; i<=cnt; i++)
			ans[i] = seq[i];
		return;
	}
	if(x > n) return;
	int nxt[30];
	for(int i=1; i<=n; i++)
		nxt[i] = f[i];
	for(int i=0; i<=1; i++){
		if(i==1){
			for(int j=1; j<=n; j++)
				if(nxt[j] & s[x]) nxt[j] |= nxt[x];
			seq[++cur] = x;
		}
		DFS(x+1, nxt);
		if(i == 1) cur--;
	}
}

signed main(){
	n = Read(), m = Read();
	s[1] = sum = 1;
	for(int i=2; i<=n; i++){
		s[i] = s[i-1] << 1;
		sum += s[i];
	}
	for(int i=1; i<=n; i++)
		f[i] |= s[i];
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		f[u] |= s[v];
		f[v] |= s[u];
	}
	cnt = n;
	DFS(1,f);
	printf("%lld\n", cnt);
	for(int i=1; i<=cnt; i++)
		printf("%lld ", ans[i]);
}