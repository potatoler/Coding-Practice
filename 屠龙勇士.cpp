#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<set>
#define int long long
using namespace std;
const int MaxN = 100005;
int T, n, m, a[MaxN], p[MaxN], c[MaxN], newa[MaxN];
multiset<int> sword;
multiset<int> :: iterator it;
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

inline int ExGCD(int a, int b, int &x, int &y){
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	int gcd = ExGCD(b, a%b, x, y);
	int t = x;
	x = y, y = t - a/b * y;
	return gcd;
}

inline int QuickMultiplication(int x, int y, int p){
	int ans = 0;
	while(y){
		if(y & 1) ans = (ans + x) % p;
		x = (x + x) % p;
		y >>= 1;
	}
	return ans;
}

inline bool Check(){
	bool f = true;
	for(int i=1;i<=n;i++)
		f &= (p[i] == 1);
	return f;
}

inline void Solve(){
	int ans = 0;
	for(int i=1;i<=n;i++)
		ans = max(ans, (a[i]/c[i]) + (a[i]%c[i] != 0));
	printf("%lld\n", ans);
	return;
}

signed main(){
	T = Read();
	while(T--){
		bool flag = true;
		n = Read(), m = Read();
		for(int i=1;i<=n;i++)
			a[i] = Read();
		for(int i=1;i<=n;i++)
			p[i] = Read();
		for(int i=1;i<=n;i++)
			newa[i] = Read();
		sword.clear();
		for(int i=1;i<=m;i++){
			int x = Read();
			sword.insert(x);
		}
		for(int i=1;i<=n;i++){
			it = sword.upper_bound(a[i]);
			if(it != sword.begin()) it--;
			c[i] = *it;
			sword.erase(it);
			sword.insert(newa[i]);
		}
		int ans = 0, z = 1;
		if(Check()){
			Solve();
			continue;
		}
		for(int i=1;i<=n;i++){
			c[i] %= p[i], a[i] %= p[i];
			if(!c[i] && a[i]){
				printf("-1\n");
				flag = false;
				break;
			}
			if(!c[i] && !a[i]) continue;
			int x, y, gcd = ExGCD(c[i], p[i], x, y);
			if(a[i] % gcd){
				printf("-1\n");
				flag = false;
				break;
			}
			p[i] /= gcd;
			a[i] = QuickMultiplication(a[i]/gcd, (x % p[i] + p[i]) % p[i], p[i]);
			gcd = ExGCD(z, p[i], x, y);
			if((a[i] - ans) % gcd){
				printf("-1\n");
				flag = false;
				break;
			}
			z = z/gcd * p[i];
			ans=(ans + QuickMultiplication( QuickMultiplication( z/p[i], ((a[i]-ans)%z+z)%z, z), (x%z+z)%z, z))%z;
		}
		if(flag) printf("%lld\n", ans);
	}
	return 0;
}