#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 1005, Mod = 1000000009;
int n, numberofGraphs[MaxN], c[MaxN][MaxN];
int QuickPow(int powerTimes){
	int baseNumber = 2, answer = 1;
	while(powerTimes){
		if(powerTimes & 1) answer = 1LL * answer * baseNumber % Mod;
		baseNumber = 1LL * baseNumber * baseNumber % Mod;
		powerTimes >>= 1;
	}
	return answer;
}
int main(){
	scanf("%d",&n);
	//Calculate combinatorial numbers
	c[0][0]=1;
	for(int i=1;i<MaxN;i++){
		c[i][i]=c[i][0]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%Mod;
	}
	//Calculate number of graphs
	for(int i=1;i<=n;i++){
		numberofGraphs[i] = QuickPow(i*(i-1)/2);
		for(int j=1;j<i;j++){
			numberofGraphs[i] = (numberofGraphs[i] - 1LL * c[i-1][j-1] * numberofGraphs[j] % Mod * QuickPow((i-j)*(i-j-1)/2) % Mod + Mod) % Mod;
		}
	}
	printf("%d", numberofGraphs[n]);
	return 0;
}