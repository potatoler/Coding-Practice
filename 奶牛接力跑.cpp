#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
const int MaxN = 102;
int n, t, s, e, cnt;
map<int, int> mp;
struct Matrix{
	int a[MaxN][MaxN];
	inline void Init(){
		memset(a, 0x3f, sizeof(a));
	}
}f, ans;

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

inline Matrix Mul(Matrix x, Matrix y){
	Matrix res;
	res.Init();
	for(int k=1; k<=cnt; k++)
		for(int i=1; i<=cnt; i++)
			for(int j=1; j<=cnt; j++)
				res.a[i][j] = min(res.a[i][j], x.a[i][k] + y.a[k][j]);
	return res;
}

inline void QuickPower(int x){
	while(x){
		if(x & 1) ans = Mul(ans, f);
		f = Mul(f, f);
		x >>= 1;
	}
}

signed main(){
	n = Read(), t = Read(), s = Read(), e = Read();
	f.Init(), ans.Init();
	for(int i=1; i<=t; i++){
		int w = Read(), u = Read(), v = Read();
		if(!mp[u]) mp[u] = ++cnt;
		if(!mp[v]) mp[v] = ++cnt;
		f.a[mp[u]][mp[v]] = f.a[mp[v]][mp[u]] = min(w, f.a[mp[u]][mp[v]]); 
	}
	for(int i=1; i<=cnt; i++)
		ans.a[i][i] = 0;
	QuickPower(n);
	printf("%lld", ans.a[mp[s]][mp[e]]);
	return 0;
}