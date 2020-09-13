#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
const int Mod = 11380;
int f[15][15][15][35], l1, l2, l3, D;

signed main(){
	scanf("%lld%lld%lld%lld",&l1,&l2,&l3,&D);
	for(int i=0;i<=D;i++)
	    f[0][0][0][i]=1;
	for(int d=1;d<=D;d++)
		for(int i=0;i<=l1;i++)
			for(int j=0;j<=l2;j++)
				for(int k=0;k<=l3;k++){
					if(i==0&&j==0&&k==0) continue;
					for(int a=0;a<i;a++)
						for(int b=0;b<=j;b++)
							for(int c=0;c<=k;c++)
								f[i][j][k][d] = (f[i][j][k][d] + f[i-a-1][j-b][k-c][d] * f[a][b][c][d-1]) % Mod;
					for(int a=0;a<j;a++)
						for(int b=0;b<=k;b++)
							f[i][j][k][d] = (f[i][j][k][d] + f[i][j-a-1][k-b][d] * f[0][a][b][d-1]) % Mod;
					for(int a=0;a<k;a++)
						f[i][j][k][d] = (f[i][j][k][d] + f[i][j][k-a-1][d] * f[0][0][a][d-1]) % Mod;
	}
	if(D == 0){
		if(l1==0 && l2==0 && l3==0) printf("1");
		else printf("0");
	}
	else if(l1==0 && l2==0 && l3==0){
		printf("0");
	}
	else printf("%lld", (f[l1][l2][l3][D] - f[l1][l2][l3][D-1] + Mod) % Mod);
	return 0;
}
