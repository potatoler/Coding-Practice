#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005;
int a[7], used[MaxN];
bool f[MaxN];

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
	while(true){
		a[0] = 0;
		for(int i=1; i<=6; i++){
			a[i] = Read();
			a[0] += a[i] * i;
		}
		if(!a[0]) break;
		// printf("%lld\n", a[0]);
		if(a[0] & 1){
			printf("Can't\n");
			continue;
		}
		memset(f, false, sizeof(f));
		a[0] >>= 1;
		f[0] = true;
		for(int i=1; i<=6; i++){
			for(int j=0; j<=a[0]; j++)
				used[j] = 0;
			for(int j=i; j<=a[0]; j++)
				if(!f[j] && f[j-i] && used[j-i] < a[i]){
					f[j] = true;
					used[j] = used[j-i] + 1;
				}
		}
		if(f[a[0]]) printf("Can\n");
		else printf("Can't\n");
	}
	return 0;
}