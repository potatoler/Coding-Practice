#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
int k, w, l1, l2;
struct BigInteger{
	int number[202], digit;
}f[1025], g[1025], ans;

//inline BigInteger operator + (BigInteger a, BigInteger b){
//	for(int i=1, j=b.digit; i<=j; i++)
//		a.number[i] += b.number[i];
//	for(int i=1, j=max(a.digit,b.digit); i<=j; i++){
//		a.number[i+1] += a.number[i] / 10;
//		a.number[i] %= 10;
//	}
//	int i;
//	for(i=max(a.digit,b.digit); a.number[i+1]!=0; i++){
//		a.number[i+1] = a.number[i] / 10;
//		a.number[i] %= 10;
//	}
//	a.digit = i;
//	return a;
//}
//
//inline BigInteger operator - (BigInteger a, BigInteger b){
//	for(int i=1, j=min(a.digit,b.digit); i<=j; i++)
//		a.number[i] -= b.number[i];
//	for(int i=1, j=max(a.digit,b.digit); i<=j; i++)
//		if(a.number[i] < 0){
//			a.number[i] += 10;
//			a.number[i+1]--;
//		}
//	for(int j=max(a.digit,b.digit); a.number[j+1]!=0; j--)
//		a.digit = j;
//	return a;
//}

//inline BigInteger operator + (BigInteger a, int b){
//	a.number[1] += b;
//	for(int i=1, j=a.digit; i<=j; i++){
//		a.number[i+1] += a.number[i] / 10;
//		a.number[i] %= 10;
//	}
//	for(int i=a.digit; a.number[i+1]!=0; i++){
//		a.digit = i;
//		a.number[i+1] = a.number[i] / 10;
//		a.number[i] %= 10;
//	}
//	return a;
//}

BigInteger operator +(BigInteger A,BigInteger B){    
		for(int j=B.digit,i=1;i<=j;i++) A.number[i]+=B.number[i];  
		for(int j=max(A.digit,B.digit),i=1;i<=j;i++)  A.number[i+1]+=A.number[i]/10,A.number[i]%=10; 
		int j;
		for(j=max(A.digit,B.digit);A.number[j+1]!=0;j++,A.number[j+1]=A.number[j]/10,A.number[j]%=10);A.digit=j;  
		return A;  
}  
BigInteger operator -(BigInteger A,BigInteger B){  
		int i,j;  
		for(j=min(A.digit,B.digit),i=1;i<=j;i++) A.number[i]-=B.number[i];  
		for(j=max(A.digit,B.digit),i=1;i<=j;i++) if (A.number[i]<0) A.number[i]+=10,A.number[i+1]--;  
		for(;A.number[j]==0;j--);A.digit=j;  
		return A;  
}  
BigInteger operator +(BigInteger A,int b){  
		int i,j;  
		A.number[1]+=b;  
		for(j=A.digit,i=1;i<=j;i++) A.number[i+1]+=A.number[i]/10,A.number[i]%=10;  
		for(;A.number[j+1]!=0;j++,A.number[j+1]=A.number[j]/10,A.number[j]%=10);A.digit=j;  
		return A;  
}  


inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	k = Read(), w = Read();
	int m = w%k, n = w/k;
	l1 = l2 = 1;
	for(int i=l1=1; i<=k; i++)
		l1 *= 2;
	l1--;
	for(int i=1; i<=l1; i++){
		f[i] = f[i-1] + 1;
//		for(int j=f[i].digit; j; j--)
//			printf("%d", f[i].number[j]);
//		printf("\n");
	}	
	for(int i=2; i<=n; i++){
		for(int j=1; j<=l1; j++)
			g[j].digit = 0;
		for(int j=1; j<=l1-i+1; j++)
			g[j] = f[l1] - f[j];
		for(int j=1; j<=l1; j++){
			ans = ans + g[j];
			f[j] = f[j-1] + g[j];
		}
	}
	for(int i=1; i<=m; i++)
		l2 *= 2;
	l2--;
	for(int i=1; i<=l2; i++)
		ans = ans + f[l1] - f[i];
	for(int i=ans.digit; i; i--)
		printf("%d", ans.number[i]);
	return 0;
}