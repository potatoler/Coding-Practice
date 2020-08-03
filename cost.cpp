#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int m,n;
int v[66][6],w[66][6],f[33333];
int cnt,p[66],num[66];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(c==0){
			p[i]=++cnt;
			v[cnt][1]=a;
			w[cnt][1]=a*b;
			num[cnt]=1;
		}
		else{
			int pos=p[c];
			num[pos]++;
			v[pos][num[pos]]=a+v[pos][1];
			w[pos][num[pos]]=a*b+w[pos][1];
		}
	}
	for(int i=1;i<=cnt;i++)
		if(num[i]==3){
			num[i]++;
			v[i][num[i]]=v[i][2]+v[i][3]-v[i][1];
			w[i][num[i]]=w[i][2]+w[i][3]-w[i][1];
		}
	// for(int i=1;i<=cnt;i++){
	// 	printf("Item set No.%d:\n",i);
	// 	for(int j=1;j<=num[i];j++)
	// 		printf("%d %d\n",v[i][j],w[i][j]);
	// 	printf("\n");
	// }
	for(int i=1;i<=cnt;i++)
		for(int j=n;j>=0;j--)
			for(int k=1;k<=num[i];k++)
				if(j>=v[i][k])
					f[j]=max(f[j],f[j-v[i][k]]+w[i][k]);
	
	printf("%d",f[n]);
	return 0;
}