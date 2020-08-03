//求 Catalan maxn=10000；
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,prime[10005],cnt,vis[20005],repeat[10005],catalan[100000],len;
void multiply(int a,int k){
    while(k--){
        for(int i=1;i<=len;++i)
        	catalan[i]*=a;
        for(int i=1;i<=len;++i)
            if(catalan[i]>=10){
                catalan[i+1]+=catalan[i]/10;
				catalan[i]%=10;
                if(i+1>len) len++;
            }
    }
}
int FOF(int num,int prime){
	int sum=0;
	while(num){
		num/=prime;
		sum+=num;
	}
	return sum;
}
int main(){
    scanf("%d",&n);
    vis[0]=vis[1]=1;
    cnt=0;
    for(int i=2;i<=2*n;++i){
        if(!vis[i]) prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<=2*n;++j){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=cnt;++i)
        repeat[i]=FOF(2*n,prime[i])-FOF(n,prime[i])-FOF(n+1,prime[i]);   //求出有多少个prime[i]因数 
    catalan[1]=1,len=1;
    for(int i=1;i<=cnt;++i)
        if(repeat[i]) multiply(prime[i],repeat[i]);
    for(int i=len;i>=1;i--)
    	printf("%d",catalan[i]);
    return 0;
}
