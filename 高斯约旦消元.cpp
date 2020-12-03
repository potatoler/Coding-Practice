#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
#define EPS 1e-8
int n;
double a[55][55], ans[55];

inline void GaussJordan(){
	int cur = 1, want = 1;
	for(int i=1; i<=n && cur<=n; i++, cur++){ // i is column
		want = cur; // these are lines
		for(int j = cur+1; j<=n; j++)
			if(fabs(a[j][i]) > fabs(a[cur][i])) want = j;
		if(fabs(a[want][i]) < EPS){
			cur--;
			continue;
		}
		if(cur != want){
			for(int j=1; j<=n+1; j++)
				swap(a[cur][j], a[want][j]);
		}
		for(int j=1; j<=n; j++){
			if(j != cur){
				for(int k=n+1; k>=cur; k--){
					a[j][k] -= a[j][i] / a[cur][i] * a[cur][k];
				}
			}
		}
	}
	return;
}

signed main(){
	scanf("%lld", &n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n+1; j++){
			scanf("%lf", &a[i][j]);
		}
	}
	GaussJordan();
	//no solution
	for(int i=1; i<=n; i++){
		bool non = true;
		for(int j=i; j<=n; j++)
			non &= (fabs(a[i][j]) < EPS);
		if(non && fabs(a[i][n+1]) > EPS){
			printf("-1\n");
			return 0;
		}
	}
	//infinity solutions
	for(int i=1; i<=n; i++){
		int cnt = 0;
		for(int j=i; j<=n; j++)
			if(fabs(a[i][j]) > EPS) cnt++;
		if(cnt > 1){
			printf("0\n");
			return 0;
		}
	}
	//solve
	for(int i=1; i<=n; i++)
		ans[i] = a[i][n+1] / a[i][i];
	for(int i=1; i<=n; i++){
		if(fabs(ans[i]) < EPS) printf("x%lld=0\n", i);
		else printf("x%lld=%.2f\n", i, ans[i]);
	}
	return 0;
}