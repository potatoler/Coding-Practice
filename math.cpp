#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 10000007;
int n, m, ans;
bool visited[MaxN];

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
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		if(visited[i]) continue;
		int cnt = 0;
		for(int j=1; i*j*j<=n; j++){
			visited[i*j*j] = true;
			cnt++;
		}
		if((int)sqrt(1.0*m/i) & 1) ans -= cnt;
		else ans += cnt;
	}
	printf("%lld", ans);
	return 0;
}