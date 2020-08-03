#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 3005;
int n, m, sum[MaxN], f[MaxN][MaxN], ans;
int deque[MaxN];

inline double Slope(int p, int x, int y){
	return (double)(f[p][x] - f[p][y] + sum[x] * sum[x] - sum[y] * sum[y]) / (double)(sum[x] - sum[y]);
}

signed main(){
	scanf("%lld%lld", &n, &m);
	memset(f, 0x3f3f3f3f, sizeof(f));
	for(int i=1;i<=n;i++){
		scanf("%lld", &sum[i]);
		sum[i] += sum[i-1];
	}
	f[0][0] = 0;
	for(int i=1;i<=n;i++)
		f[1][i]=sum[i] * sum[i];
	for(int p=2;p<=m;p++){
		int head = 1, tail = 0;
		for(int i=1;i<=n;i++){
			while(head < tail && Slope(p-1, deque[head], deque[head+1]) < 2*sum[i]) head++;
			int j = deque[head];
			f[p][i] = f[p-1][j] + (sum[j] - sum[i]) * (sum[j] - sum[i]);
			while(head < tail && Slope(p-1, deque[tail-1], deque[tail]) > Slope(p-1, deque[tail], i)) tail--;
			deque[++tail] = i;
		}
	}
	ans = m * f[m][n] - sum[n] * sum[n];
	printf("%lld", ans);
	return 0;
}