#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,num[10];
long long f[35][35][35][35][35];
void work(){
	memset(num,0,sizeof(num));
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	f[0][0][0][0][0]=1;
	for(int a=0;a<=num[1];++a)
		for(int b=0;b<=num[2];++b)
			for(int c=0;c<=num[3];++c)
				for(int d=0;d<=num[4];++d)
					for(int e=0;e<=num[5];++e){
						if(a<num[1]) 	  f[a+1][b][c][d][e]+=f[a][b][c][d][e];
						if(b<num[2]&&b<a) f[a][b+1][c][d][e]+=f[a][b][c][d][e];
						if(c<num[3]&&c<b) f[a][b][c+1][d][e]+=f[a][b][c][d][e];
						if(d<num[4]&&d<c) f[a][b][c][d+1][e]+=f[a][b][c][d][e];
						if(e<num[5]&&e<d) f[a][b][c][d][e+1]+=f[a][b][c][d][e];
						}
		printf("%lld\n",f[num[1]][num[2]][num[3]][num[4]][num[5]]);
}
int main(){
	while(cin>>n,n)

	return 0;
}