#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef unsigned long long ll;
int n;
ll numerator, denominator, integerPart;
int integerLength, fractionLength;
ll GCD(ll x, ll y){
	return y?GCD(y, x%y):x;
}
int GetLength(ll x){
	int numberLength=0;
	while(x){numberLength++, x/=10;}
	return numberLength;
}
int main(){
	while(scanf("%d",&n) != EOF){
		numerator = 0, denominator = 1, integerPart = 0;
		for(int i=1;i<=n;i++){
			numerator *= i;
			numerator += denominator * n;
			denominator *= i;
			ll tmp = GCD(numerator, denominator);
			numerator /= tmp, denominator /= tmp;
			tmp = numerator / denominator;
			integerPart += tmp;
			numerator -= denominator * tmp;

		}
		integerLength = GetLength(integerPart) + 1;
		fractionLength = max(GetLength(numerator), GetLength(denominator));
		if(!numerator) printf("%lld\n",integerPart);
		else{
			for(int i=1;i<=integerLength;i++) printf(" ");
			printf("%lld\n",numerator);
			printf("%lld ",integerPart);
			for(int i=1;i<=fractionLength;i++) printf("-");
			printf("\n");
			for(int i=1;i<=integerLength;i++) printf(" ");
			printf("%lld\n",denominator);
		}
	}
	return 0;
}