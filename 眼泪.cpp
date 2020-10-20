#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, type, m, f[MaxN][2], a[MaxN], g[MaxN];
// f[x][0] for increasing, f[x][1] for decreasing;
map<int,int> mp;

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

inline void Init1(){
	f[n][0] = n;
	for(int i=n-1; i; i--){
		if(a[i] <= a[i+1]) f[i][0] = f[i+1][0];
		else f[i][0] = i;
	}
	return;
}

inline void Init2(){
	f[n][0] = f[n][1] = n;
	for(int i=n-1; i; i--){
		if(a[i] < a[i+1]){
			f[i][0] = f[i+1][0];
			f[i][1] = i;
		}
		else if(a[i] > a[i+1]){
			f[i][0] = i;
			f[i][1] = f[i+1][1];
		}
		else{
			f[i][0] = f[i+1][0];
			f[i][1] = f[i+1][1];
		}
	}
	return;
}

signed main(){
	n = Read(), type = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	if(type == 1) Init1();
	else Init2();
	for(int i=1; i<=n; i++)
		g[i] = max(f[i][0], f[i][1]);
	int lastpos = 0;
	for(int i=1; i<n; i++){
		if(g[i] == g[i+1]) continue;
		int xi = i, yi = g[i], xj = i+1, yj = g[i+1];
		int right = (g[xj] >= g[xi] + 2);
		for(int j=xi-1; j>lastpos; j--){
			right = !(right & 1);
			mp[j+yi+2] = right;
		}
		int up = (g[xi] == g[xi-1]);
		for(int j=yi+2; j<=yj; j++){
			up = !(up & 1);
			mp[xi-1+j] = up;
		}
		mp[xj-2+yj+1] = 1;
		mp[xj+yj] = 0;
		mp[xj-1+yj+2] = 1;
		lastpos = xj-1;
	}
	m = Read();
	while(m--){
		int l = Read(), r = Read();
		if(g[l] >= r){
			printf("liulei\n");
			continue;
		}
		else if(g[l] == r-1){
			printf("se\n");
			continue;
		}
		else if(g[l] < r && g[l+1] >= r){
			printf("se\n");
			continue;
		}
		else{
			if(mp[l+r] == 0) printf("liulei\n");
			else printf("se\n");
		}
	}
	return 0;
}