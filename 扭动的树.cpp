#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 302, Mod = 1000000007;
int n, ans = -1, key[MaxN], value[MaxN], sum[MaxN], f[MaxN][MaxN][2];
bool edge[MaxN][MaxN], visited[MaxN][MaxN][2];
struct Vertex{
	int key, value;
	bool operator < (const Vertex &a) const{
		return key < a.key;
	}
}vertex[MaxN];

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

inline int GCD(int x, int y){
	return y == 0 ? x : GCD(y, x%y);
}

inline int DP(int l, int r, int father){
	if(l > r) return 0;
	if(visited[l][r][father]) return f[l][r][father];
	visited[l][r][father] = true;
	int &ans = f[l][r][father] = -1;
	int fa = father == 0 ? l-1 : r+1;
	for(int root = l; root <= r; root++){
		if(edge[root][fa]){
			if(DP(l, root-1, 1) == -1 || DP(root+1, r, 0) == -1) continue;
			ans = max(ans, f[l][root-1][1] + f[root+1][r][0] + sum[r] - sum[l-1]);
		}
	}
	return ans;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		vertex[i].key = Read(), vertex[i].value = Read();
	sort(vertex+1, vertex+1+n);
	for(int i=1; i<=n; i++){
		key[i] = vertex[i].key, value[i] = vertex[i].value;
		sum[i] = sum[i-1] + value[i];
	}
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			if(GCD(key[i], key[j]) != 1) edge[i][j] = edge[j][i] = true;
	for(int i=1; i<=n; i++){
		if(DP(1, i-1, 1) == -1 || DP(i+1, n, 0) == -1) continue;
		ans = max(ans, DP(1, i-1, 1) + DP(i+1, n, 0) + sum[n]);
	}
	printf("%lld", ans);
	return 0;
}