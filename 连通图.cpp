#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN=102, MaxM=1003;
int n, m, i, j, k;
struct BigInteger{
	int digit[MaxM], length;
}f[MaxN], power[MaxN];

inline BigInteger operator / (const BigInteger &x,const int y){
	BigInteger cur;
	memset(cur.digit,0,sizeof cur.digit);
	cur.length=0;
	int ns=0;
	for(int i=x.length; i>=1; i--){
		ns=ns*10+x.digit[i];
		cur.digit[i]=ns/y;
		ns%=y;
		if(!cur.length && cur.digit[i]) cur.length=i;
	}
	return cur;
}

inline BigInteger operator + (const BigInteger &x,const BigInteger &y){
	BigInteger cur;
	memset(cur.digit,0,sizeof cur.digit);
	for(int i=1; i<=max(x.length,y.length); i++){
		cur.digit[i]+=x.digit[i]+y.digit[i];
		cur.digit[i+1]=cur.digit[i]/10;
		cur.digit[i]%=10;
	}
	cur.length=max(x.length,y.length);
	if(cur.digit[cur.length+1]) 
		cur.length++;
	return cur;
}

inline BigInteger operator * (const BigInteger &x,const BigInteger &y){
	BigInteger cur;
	memset(cur.digit,0,sizeof cur.digit);
	for(int i=1; i<=x.length; i++)
		for(int j=1; j<=y.length; j++){
			cur.digit[i+j-1]+=x.digit[i]*y.digit[j];
			cur.digit[i+j]+=cur.digit[i+j-1]/10;
			cur.digit[i+j-1]%=10;
		}
	cur.length=x.length+y.length-1;
	if(cur.digit[cur.length+1]) cur.length++;
	return cur;
}

inline BigInteger C(int x,int y){
	BigInteger tot,temp;
	tot.length=1;
	tot.digit[1]=1;
	for(int i=y,j=1; j<=x; i--,j++){
		int t=i;
		temp.length=0;
		while(t){
			temp.digit[++temp.length]=t%10;
			t/=10;
		}
		tot=tot*temp/j;
	}
	return tot;
}

inline void print(const BigInteger &x){
	for(int i=x.length; i>=1; i--)
		printf("%lld",x.digit[i]);
	printf("\n");
}

inline void Init(){
	for(int i=1; i<=50; i++){
		int temp=((int)(1)<<i)-1;
		while(temp){
			power[i].digit[++power[i].length]=temp%10;
			temp/=10;
		}
	}
	f[1].length=1;f[1].digit[1]=1;f[2].length=1;f[2].digit[1]=1;
	for(int i=3; i<=50; i++)
		for(int j=1; j<=i-1; j++)
			f[i]=f[i]+C(j-1,i-2)*f[j]*f[i-j]*power[j];
}

signed main(){
	Init();
	while(scanf("%lld",&n) && n) 
		print(f[n]);
	return 0;
}