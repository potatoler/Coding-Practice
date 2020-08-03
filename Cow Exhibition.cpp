#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 405, MaxValue = 400000;
int n, IQ[MaxN], EQ[MaxN], f[MaxValue*2 + 10], ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d", &IQ[i], &EQ[i]);
	memset(f, -0x3f, sizeof(f));
	f[0 + MaxValue] = 0;
	for(int i=1;i<=n;i++){
		if(IQ[i] > 0){
			for(int j=MaxValue;j>=-MaxValue;j--){
				if(j - IQ[i] >= -MaxValue && j - IQ[i] <= MaxValue)
				f[j+MaxValue] = max(f[j+MaxValue], f[j-IQ[i]+MaxValue] + EQ[i]);
			}
		}
		else{
			for(int j=-MaxValue;j<=MaxValue;j++){
				if(j - IQ[i] >= -MaxValue && j - IQ[i] <= MaxValue) f[j+MaxValue] = max(f[j+MaxValue], f[j-IQ[i]+MaxValue] + EQ[i]);
			}
		}
	}
	for(int i=0;i<=MaxValue;i++)
		if(f[i + MaxValue] >= 0) ans = max(i + f[i+MaxValue], ans);
	printf("%d",ans);
	return 0;
}