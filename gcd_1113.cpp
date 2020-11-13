#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int n, a[MaxN], pos[MaxN], value[MaxN], cnt, ans;

class BinaryIndexedTree{
	private:
	int f[MaxN], g[MaxN];
	
	public:
	#define lowbit(x) (x&(-x))
	
	inline void Add(int x, int w){
		for(int i=x; i<=n; i += lowbit(i)){
			f[i] += w;
			g[i] += (x-1) * w;
		}
	}
	
	inline int Query(int x){
		int res = 0;
		for(int i=x; i; i -= lowbit(i))
			res = (res + x*f[i] - g[i]) % Mod;
		return res;
	}
}BIT;

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
	return y? GCD(y,x%y) : x;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=cnt; j++)
			value[j] = GCD(value[j], a[i]);
		value[++cnt] = a[i];
		pos[cnt] = i;
		int cur = cnt;
		cnt = 0;
		for(int j=1; j<=cur; j++){
			if(value[j] != value[j-1]){
				value[++cnt] = value[j];
				pos[cnt] = pos[j];
			}
		}
		for(int j=1; j<cnt; j++){
			BIT.Add(pos[j], value[j]);
			BIT.Add(pos[j+1], -value[j]);
		}
		BIT.Add(pos[cnt], value[cnt]);
		BIT.Add(i+1, -value[cnt]);
	}
	ans = (BIT.Query(n) - BIT.Query(0) + Mod) % Mod;
	printf("%lld", ans);
	return 0;
}