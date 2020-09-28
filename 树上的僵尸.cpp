#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 2003, MaxM = 2000006, Mod = 998244353;
int n, m, k, head[MaxM], cntEdge, father[MaxM], depth[MaxM], cnt[MaxN][MaxN], sum, ans, t[MaxM];
bool chain = true;
struct Edge{
	int destination, nextEdge;
}edge[MaxM*2];
#define thisSon edge[i].destination
#define itsFather father[x]

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

inline void DFS1(int x, int root){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father[x]) continue;
		father[thisSon] = x;
		DFS1(thisSon, root);
	}
	return;
}

inline void DFS(int x, int root){
	depth[x] = depth[father[x]] + 1;
	cnt[root][depth[x]]++;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father[x]) continue;
		father[thisSon] = x;
		DFS(thisSon, root);
	}
	return;
}

inline void Chain(){
	for(int i=1; i<=n; i++)
		sum = (sum + min(i+k, n) - i + 1) % Mod;
	sum = QuickPower(sum, m);
	for(int i=1; i<=n; i++)
		t[i] = (min(n, i+k) + t[i-1]) % Mod;
	for(int i=1; i<=n; i++){
		int count = i- max(1ll, i-k) + 1, res = t[i] - t[max(1ll, i-k)-1];
		res = (res - count*i%Mod + Mod) % Mod;
		int all = (res + count) % Mod;
		ans = (ans + QuickPower(all, m) - QuickPower(res, m) + Mod) % Mod;
	}
	ans = (sum - ans + Mod) % Mod;
	printf("%lld", ans);
	return;
}

inline void Calculate(int x){
	depth[x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		memset(cnt[thisSon], 0, sizeof(cnt[thisSon]));
		father[thisSon] = x;
		DFS(thisSon, thisSon);
	}
	for(int i=1; i<=k+1; i++)
		cnt[0][i] = 1;
	int res = 0, all = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father[x]) continue;
		for(int j=1; j<=k+1; j++)
			all = (all + cnt[thisSon][j] * cnt[0][k+2-j]) % Mod;
		int tmp = 0;
		for(int j=1; j<=k+1; j++){
			tmp = (tmp + cnt[thisSon][j]) % Mod;
			cnt[0][j] = (cnt[0][j] + tmp) % Mod;
		}
	}
	if(father[x]){
		int passFather = 0;
		for(int j=1; j<=k+1; j++)
			passFather = (passFather + cnt[itsFather][j] * cnt[0][k+2-j]) % Mod;
		all = (all + passFather) % Mod;
		res = passFather;
		int tmp = 0;
		for(int j=1; j<=k+1; j++){
			tmp = (tmp + cnt[itsFather][j]) % Mod;
			cnt[0][j] = (cnt[0][j] + tmp) % Mod;
		}
	}
	sum = (sum + QuickPower(all, m) - QuickPower(res, m) + Mod) % Mod;
	ans = (ans + cnt[0][k+1]) % Mod;
}

signed main(){
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	DFS1(1,0);
	for(int i=2; i<=n; i++)
		if(father[i] != i-1) chain = false;
	if(chain) Chain();
	else if(k ==0){
		ans = (QuickPower(n, m) - n + Mod) % Mod;
		printf("%lld", ans);
	}
	else{
		DFS(1,0);
		for(int i=1; i<=n; i++)
			Calculate(i);
		ans = (ans + n) / 2;
		ans = (QuickPower(ans, m) - sum + Mod) % Mod;
		printf("%lld", ans);
	}
	return 0;
}