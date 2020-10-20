#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 50004;
int T, n, sum[MaxN], tot[MaxN];
struct Child{
	int a, b;
	bool operator < (const Child &y) const{
		if (min(a,y.b) == min(y.a,b)) return a < y.a;
		return min(a,y.b) < min(y.a,b);
	}
}child[MaxN];

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
	T = Read();
	while(T--){
		n = Read();
		for(int i=1; i<=n; i++)
			child[i].a = Read(), child[i].b = Read();
		sort(child+1, child+1+n);
		sum[1] = child[1].a;
		for(int i=2; i<=n; i++)
			sum[i] = sum[i-1] + child[i].a;
		tot[1] = child[1].a + child[1].b;
		for(int i=2; i<=n; i++)
			tot[i] = max(tot[i-1], sum[i]) + child[i].b;
		printf("%lld\n", tot[n]);
	}
	return 0;
}