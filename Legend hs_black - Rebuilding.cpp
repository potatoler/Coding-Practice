#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, a[MaxN], tmp[MaxN];

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

inline bool Judge(int t){
	memcpy(tmp, a, sizeof(a));
	int line = n;
	for(int i=1; i<=m; i++){
		while(line && !tmp[line]) line--;
		if(!line) return true;
		else if(line > t) return false;
		int todo = t - line;
		while(line && todo){
			int need = min(todo, tmp[line]);
			while(line && !tmp[line]) line--;
			todo -= need;
			tmp[line] -= need;
		}
	}
	while(line && !tmp[line]) line--;
	if(!line) return true;
	else return false;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	int l = 0, r = 1e14+1e10;
	while(l<=r){
		int mid = (l+r) >> 1;
		if(Judge(mid)) r = mid-1;
		else l = mid+1;
	}
	printf("%lld", l);
	return 0;
}