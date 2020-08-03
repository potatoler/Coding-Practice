#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 1005;
const int MaxA = 15000005;
using namespace std;
int n, cntPrime, maxNumber, cntOne, a[MaxN], primeNumber[MaxA * 2];
bool isPrime[MaxA * 2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		maxNumber = max(a[i], maxNumber);
		if(a[i] == 1) cntOne++;
	}
	for(int i=1;i<=maxNumber*2;i++)
		isPrime[i] = true;
	for(int i=2;i<=maxNumber*2;i++){
		if(isPrime[i]) primeNumber[++cntPrime] = i;
		for(int j=1;j<=cntPrime;j++){
			if(i * primeNumber[j] > maxNumber * 2) break;
			isPrime[i * primeNumber[j]] = false;
		}
	}
	if(cntOne > 2){
		int x = 0;
		for(int i=1;i<=n;i++)
			if (a[i] != 1 && isPrime[a[i]+1])
				x = max(x,a[i]);
		if(x==0){
			printf("%d\n",cntOne);
			for(int i=1;i<=cntOne;i++)
				printf("1 ");
			printf("\n");
		}
		else{
			printf("%d\n",cntOne+1);
			for(int i=1;i<=cntOne;i++)
				printf("1 ");
			printf("%d\n",x);
		}
	}
	if(cntOne == 2){
		int x = 0, y = 0, w = 0;
		for(int i=1;i<=n;i++)
			if(a[i] != 1 && isPrime[a[i]+1])
				x=max(x,a[i]);
		if(x)
			printf("3\n1 1 %d\n",x);
		else{
			for(int i=1;i<n;i++)
				for(int j=i+1;j<=n;j++)
					if(isPrime[a[i]+a[j]] && a[i]+a[j] > w){
						w=a[i]+a[j];
						x=a[i];
						y=a[j];
					}
			if(x>y) swap(x, y);
			printf("2\n%d %d\n",x,y);
		}
	}
	if(cntOne < 2){
		int x = 0, y = 0, w = 0;
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
				if(isPrime[a[i]+a[j]] && a[i]+a[j] > w){
					w=a[i]+a[j];
					x=a[i];
					y=a[j];
				}
		if(x>y) swap(x, y);
		printf("2\n%d %d\n",x,y);
	}
	return 0;
}