#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
#define double long double
signed main(){
	int T;
	scanf("%d", &T);
	while(T--){
		double x, y, k, b;
		scanf("%Lf%Lf%Lf%Lf", &x, &y, &k, &b);
		b = -b / (k+1), k = (1-k) / (k+1);
		double xp = (x+y) / 2, yp = (x-y) / 2;
//		printf("%.3f %.3f %.3f %.3f\n", b, k, xp, yp);
		double ans = 0.0;
		if(k > 0){
			if(k > 1){
				double xq = (yp-b) / k;
				ans = fabs(xp - xq);
			}
			else{
				double yq = k * xp + b;
				ans = fabs(yp - yq);
			}
		}
		else{
			if(k > -1){
				double yq = k * xp + b;
				ans = fabs(yp - yq);
			}
			else{
				double xq = (yp-b) / k;
				ans = fabs(xp - xq);
			}
		}
		printf("%.3Lf\n", ans);
	}
}