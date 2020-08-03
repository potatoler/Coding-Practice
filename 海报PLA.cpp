#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 250010;
int stack[MaxN], top, n;
int main(){
	scanf("%d",&n);
	int ans = n;
	int a, b;
	for(int i=1;i<=n;i++){
		scanf("%d%d", &a, &b);
		while(stack[top] >= b){
			if(stack[top] > b) top--;
			else{
				top--;
				ans--;
			}
		}
		stack[++top] = b;
	}
	printf("%d",ans);
	return 0;
}