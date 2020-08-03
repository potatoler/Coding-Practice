#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef lon g long ll;
int n,m,N,tot,s[105],w[105];
ll ans,f[105][105][105];
int get(int x){
	int sum=0;
	while(x){
		++sum;
		x&=x-1;
	}
	return sum;
}
int main(){
	scanf("%d%d",&n,&m);
	N=1<<n;
	for(int i=0;i<N;i++){
		if(i&i<<1) continue;
		s[++tot]=i;
		w[tot]=get(i);
		f[1][tot][w[tot]]=1;
	}
	for(int i=2;i<=n;i++)
		for(int j=1;j<=tot;j++)
			for(int k=1;k<=tot;k++){
				if(s[j]&s[k]) continue;
				if(s[j]&s[k]<<1) continue;
				if(s[k]&s[j]<<1) continue;
				for(int l=w[j];l<=m;l++)
					f[i][j][l]+=f[i-1][k][l-w[j]];
			}
	for(int i=1;i<=tot;i++)
		ans+=f[n][i][m];
	printf("%lld\n",ans);
	return 0;
}