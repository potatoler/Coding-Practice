#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
//#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int MaxN = 102, MaxM = 11;
int n, m, ans;
int f[2][1<<MaxM][1<<MaxM], bin[MaxN], state[1<<MaxM], cntState;
char mp[MaxN][MaxM];

inline int Read() {
	int num = 0, op = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

inline bool OK(int s){
	for(int i=0; i<m; i++){
		if((s>>i & 1) && (((s>>(i+1)) & 1) | ((s>>(i+2)) & 1))) return false;
	}
	return true;
}

inline int GetOne(int s){
	int res = 0;
	while(s){
		s -= lowbit(s);
		res++;
	}
	return res;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		scanf("%s", mp[i]+1);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(mp[i][j] == 'H') bin[i] |= 1<<(m-j);
		}
	}
	for(int i=0; i<(1<<m); i++)
		if(OK(i)) state[++cntState] = i;
	int pos = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=cntState; j++){
			for(int k=1; k<=cntState; k++){
				for(int l=1; l<=cntState; l++){
					int x = state[j], y = state[k], z = state[l];
					if((x & y) | (x & z) | (x & z)) continue;
					if((x & bin[i]) | (y & bin[i-1])) continue;
					f[pos][j][k] = max(f[pos][j][k], f[pos^1][k][l] + GetOne(x));
					ans = max(ans, f[pos][j][k]);
				}
			}
		}
		pos^=1;
	}
	printf("%d", ans);
	return 0;
}