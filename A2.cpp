#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,a[maxn];
double cnt[maxn];
double factorial(double m){
		if(m==1) return 1;
		else return m*factorial(m-1);
}
int main(){
	scanf("%d",&n);
	int maxNumber=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		cnt[a[i]]++;
		maxNumber=max(maxNumber,a[i]);
	}
	double numberExpect=0;
	for(int i=0;i<=maxNumber;i++){
		if(cnt[i]==0) continue;
		numberExpect+=(double)cnt[i]/factorial(cnt[i]);
	}
	printf("%.0lf",floor(numberExpect));
	return 0;
}