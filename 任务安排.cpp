#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
const int MaxN = 5005;
int f[MaxN], t[MaxN], v[MaxN], n, s, q[MaxN];
int main(){
	scanf("%d%d", &n, &s);
	for(int i=1;i<=n;i++){
		scanf("%d%d", &t[i], &v[i]);
		t[i] += t[i-1];
		v[i] += v[i-1];
		f[i] = INT_MAX;
	}
	int l = 1, r = 1;
	for(int i=1;i<=n;i++){
		while(l < r && f[q[l+1]] - f[q[l]] <= (s + t[i]) * (v[q[l+1]] - v[q[l]])) l++;
		f[i] = f[q[l]] + t[i] * v[i] + s * v[n] - v[q[l]] * (s + t[i]);
		while(l < r && (f[i] - f[q[r]]) * (v[q[r]] - v[q[r-1]]) <= (f[q[r]] - f[q[r-1]]) * (v[i] - v[q[r]])) r--;
		q[++r] = i;
	}
	printf("%d",f[n]);
	return 0;
}