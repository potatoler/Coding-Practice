#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = (1<<18) + 10, MaxM = 102;
int digit[20], cnt = -1, m, n, f[MaxN][MaxM];
bool visited[10];

signed main(){
	scanf("%lld%lld", &n, &m);
	for( ; n; n /= 10)
		digit[++cnt] = n % 10;
	f[0][0] = 1;
	for(int s=1; s<(1<<cnt+1); s++){
		memset(visited, false, sizeof(visited));
		for(int i=0; i<=cnt; i++){
			if(s == (1<<i) && !digit[i]) break;
			if(!(s & (1<<i)) || visited[digit[i]]) continue;
			visited[digit[i]] = true;
			for(int j=0; j<m; j++)
				f[s][(j * 10 + digit[i]) % m] = f[s][(j * 10 + digit[i]) % m] + f[s ^ (1<<i)][j];
		}
	}
	printf("%lld", f[(1<<cnt+1)-1][0]);
	return 0;
}