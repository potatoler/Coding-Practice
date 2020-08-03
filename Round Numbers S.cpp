#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int l, r, c[32][32];

void InitC(){
	for(int i=1;i<=31;i++){
		c[i-1][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	return;
}

inline int Statistic(int l,int k){
	int ans=0;
	for(int i=l;i-(l-i)>=k;i--) //i zero(s?)
		ans+=c[l][i];
	return ans;
}

inline int f(int x){
	int ans = 0, cnt = 0, digit[32]; 
	while(x != 0){
		digit[++cnt] = ((x&1)==1);
		x >>= 1;
	}
	for(int i=1;i<cnt;i++)
		ans += Statistic(i-1, 1);//Why 1? Because there is a 1 at the first digit;
	int k = 1;
	for(int i=cnt-1;i>=1;i--){
		if(digit[i]){
			ans += Statistic(i-1,k-1);//Why k-1? Because we cut the last part into small pieces, so there's one digit missed;
			k++;
		}
		else k--;
	}
	if(k<=0) ans++;
	return ans;
}

int main(){
	scanf("%d%d",&l,&r);
	InitC();
	printf("%d\n",f(r) - f(l-1));
	return 0;
}