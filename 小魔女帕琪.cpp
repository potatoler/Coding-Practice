#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
int a[8], n;
double ans = 1;
int main(){
	for(int i=1;  i<=7;i++){
		scanf("%d", &a[i]);
		n += a[i];
	}
	for(int i=1;i<=6;i++)
		ans = ans * a[i] / (double)(n+1-i) *(double)(i);
	ans = ans * a[7] * 7;
	printf("%.3lf\n",ans);
	return 0;
}