#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 250, MAXR = 150;
int n, r, d[MAXN], T;
double p[MAXN], sump[MAXN], f[MAXN][MAXR];
double fac[MAXN][MAXN];// (1 - p[i]) ^ j

void Init(){
	for(int i=0;i<n;i++) {
		fac[i][0]=1;
		for(int j=1;j<=r;j++)
			fac[i][j] = fac[i][j-1] * (1-p[i]);
	}
}

double Solve(){
	memset(f,0,sizeof(f));
	memset(sump,0,sizeof(sump));
	f[0][0] = fac[0][r];
	f[0][1] = sump[0] = 1-f[0][0];
	for(int i=1;i<n;i++){
		for(int j=0;j<=r;j++){
			sump[i] += f[i-1][j] * (1 - fac[i][r-j]);
			f[i][j] += f[i-1][j] * fac[i][r-j];
			if(j) f[i][j] += f[i-1][j-1] * (1 - fac[i][r-j+1]);
		}
	}
	double ans = 0;
	 for(int i=0;i<n;i++)
		ans += d[i] * sump[i];
	return ans;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n, &r);
		for(int i=0;i<n;i++)
 			scanf("%lf%d",&p[i], &d[i]);
		Init();
		printf("%.10lf\n",Solve());
	}
	return 0;
}
//O(nTr)