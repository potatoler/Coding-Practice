#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 10005, MaxM = 2005;
int n, m, k;
int f[MaxN][MaxM], raiseHeight[MaxN], dropHeight[MaxN], floorHeight[MaxN], ceilHeight[MaxN], ans;
bool doHaveTube[MaxN];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d", &raiseHeight[i], &dropHeight[i]);
		floorHeight[i] = 1;
		ceilHeight[i] = m;
	}
	for(int i=1;i<=k;i++){
		int p, l, h;
		scanf("%d%d%d", &p, &l, &h);
		doHaveTube[p] = true;
		floorHeight[p] = l + 1;
		ceilHeight[p] = h - 1;
	}
	memset(f, 0x3f, sizeof(f));
	for(int i=1;i<=m;i++)
		f[0][i]=0;
	for(int i=1;i<=n;i++){
		for(int j = raiseHeight[i] + 1; j <= m + raiseHeight[i]; j++)
			f[i][j] = min(f[i-1][j-raiseHeight[i]] + 1, f[i][j-raiseHeight[i]] + 1);
		for(int j = m+1; j <= m + raiseHeight[i]; j++)
			f[i][m] = min(f[i][m], f[i][j]);
		for(int j = 1; j <= m-dropHeight[i]; j++)
			f[i][j] = min(f[i][j], f[i-1][j+dropHeight[i]]);
		for(int j=1; j < floorHeight[i]; j++)
			f[i][j] = f[0][0];
		for(int j = ceilHeight[i]+1; j<=m; j++)
			f[i][j] = f[0][0];
	}
	ans = f[0][0];
	for(int i=1;i<=m;i++)
		ans = min(f[n][i], ans);
	//printf("%d",ans);
	//return 0;
	if(ans < f[0][0]) printf("1\n%d", ans);
	else{
		int i;
		for(i=n;i>=1;i--){
			int j;
			for(j=1;j<=m;j++)
				if(f[i][j] < f[0][0]) break;
			if(j <= m) break;
		}
		ans = 0;
		for(int j=1;j<=i;j++)
			if(doHaveTube[j]) ans++;
		printf("0\n%d",ans);
	}
	return 0;
}