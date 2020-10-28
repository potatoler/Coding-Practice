#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, l, pos, f[MaxN];

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
//	freopen("river.in", "r", stdin);
//	freopen("river.my", "w", stdout);
	n = Read(), l = Read();
	f[0] = INT_MAX;
	for(int i=1; i<=n; i++){
		int x = i<n? Read() : INT_MAX;
		while(pos + l < i) pos++;
		while(x && pos < i){
			if(f[pos] > x){
				f[i] += x;
				f[pos] -= x;
				x = 0;
			}
			else{
				f[i] += f[pos];
				x -= f[pos];
				f[pos] = 0;
				pos++;
			}
		}
	}
	printf("%lld", f[n]);
	return 0;
}