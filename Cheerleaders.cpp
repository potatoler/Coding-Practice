#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int mod=1e6+7,maxn=405;
int n,m,k,T;
int c[maxn][maxn],ans;
void init(){//Calculate value of combinatorial number at the very first.
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<maxn;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
}
int main(){
	init();
	scanf("%d",&T);
	for(int gameRound=1;gameRound<=T;gameRound++){
		ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int gameCase=0;gameCase<16;gameCase++){
			int fieldRow=n,fieldColumn=m,situationSummary=0;
			if(gameCase&1) fieldRow--,situationSummary++;
			if(gameCase&2) fieldRow--,situationSummary++;
			if(gameCase&4) fieldColumn--,situationSummary++;
			if(gameCase&8) fieldColumn--,situationSummary++;
			if(situationSummary&1) ans=(ans+mod-c[fieldRow*fieldColumn][k])%mod;
			//Plus "mod" to avoid "ans" becoming a negative.
			else ans=(ans+c[fieldRow*fieldColumn][k])%mod;
		}
		printf("Case %d: %d\n",gameRound,ans);
	}
	return 0;
}

