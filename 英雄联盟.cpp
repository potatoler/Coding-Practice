#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, ans, k[MaxN], c[MaxN], f[MaxN], sum;

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
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)	
		k[i] = Read();
	for(int i=1; i<=n; i++){
		c[i] = Read();
		sum += c[i] * k[i];
	}
	f[0] = 1;
	for(int i=1; i<=n; i++)
		for(int j=sum; j>=0; j--)
			for(int l=1; l<=k[i]; l++)
				f[j] = max(f[j], f[j-l*c[i]] * l);
	while(true){
		if(ans > sum) break;
		if(f[ans] >= m) break;
		ans++;
	}
	printf("%lld", ans);
	return 0;
}