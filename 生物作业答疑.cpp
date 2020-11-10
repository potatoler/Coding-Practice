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
int T, n, k, a[MaxN];
bool exist;

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

inline bool Judge(){
	if(!exist) return false;
	else if(n == 1) return true;
	else{
		for(int i=1; i<=n; i++)
			if(a[i]>=k && ((a[i+1]>=k && i+1<=n) || (a[i+2]>=k && i+2<=n))) return true;
		return false;
	}
}

signed main(){
	T = Read();
	while(T--){
		exist = false;
		n = Read(), k = Read();
		for(int i=1; i<=n; i++){
			a[i] = Read();
			if(a[i] == k) exist = true;
		}
		printf(Judge()? "yes\n" : "no\n");
	}
	return 0;
}