#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003;
int n, f[MaxN], ans, cnt;
struct Missile{
	int x, y, z;
	bool operator < (const Missile &a) const{
		return x < a.x;
	}
}missile[MaxN];

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
	n = Read();
	for(int i=1; i<=n; i++)
		missile[i] = (Missile){Read(), Read(), Read()};
	sort(missile+1, missile+1+n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(missile[i].x < missile[j].x && missile[i].y < missile[j].y && missile[i].z < missile[j].z) f[j] = max(f[j], f[i]+1), ans = max(ans, f[j]);
	ans = ans + 1;
	cnt = n%ans? n/ans+1 : n/ans;
	printf("%lld\n%lld\n", ans, cnt);
	return 0;
}