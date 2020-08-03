#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,a[maxn],cnt[maxn];
struct Number{
	int val;
	double cnt;
}num[maxn];
bool cmp(Number x,Number y){
	return x.cnt<y.cnt;
}
int main(){
	scanf("%d",&n);
	int maxNumber=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		maxNumber=max(maxNumber,a[i]);
		num[a[i]].cnt++;
	}
	double lastMultiplication=1;
	double numberExpect=0;
	sort(num,num+maxNumber+1,cmp);
	for(int i=0;i<=maxNumber;i++){
		//printf("%lf ",numberExpect);
		if(num[i].cnt==0) continue;
		if(num[i].cnt==1) numberExpect++;
		else{
			if(num[i].cnt==num[i-1].cnt) numberExpect+=(double)num[i].cnt/lastMultiplication;
			else{
				for(int j=num[i-1].cnt+1;j<=num[i].cnt;j++)
					lastMultiplication*=j;
				numberExpect+=(double)num[i].cnt/lastMultiplication;
			}
		}
		//printf("%lf\n",numberExpect);
	}
	//for(int i=0;i<=maxNumber;i++) printf("%lf ",num[i].cnt);printf("\n");
	printf("%.0lf",floor(numberExpect));
	return 0;
}