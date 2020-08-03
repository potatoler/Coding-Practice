#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,D,p,L,v,problemCase;
double answer;
int main(){
	while(scanf("%d%d",&n,&D)!=EOF){
		if(D==0) break;
		answer=0.0;
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&p,&L,&v);
			D-=L;
			answer+=2.0*L/v;
		}
		printf("Case %d: %.3lf\n",++problemCase,answer+(double)D);
	}
	return 0;
}