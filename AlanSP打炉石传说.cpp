#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m;
bool a[MaxN];

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

inline int Calculate(int x){
	int p=0, res = 0;
	while(true){
		res++;
		int cnt = 0;
		for(int i=1; i<=x; i++){
			if(a[++p]) cnt++;
		}
		if(!cnt) return res;
	}
}

signed main(){
	n = Read(), m = Read();
	while(m--){
		int op = Read();
		if(op == 1){
			int h = Read();
			a[h] = true;
		}
		else{
			int l = Read(), r = Read();
			int res = 0;
			for(int i=l; i<=r; i++)
				res += Calculate(i);
			printf("%lld\n", res);
		}
	}
	return 0;
}