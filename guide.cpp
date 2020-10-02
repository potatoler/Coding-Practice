#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define int long long
using namespace std;
const int MaxN = 100005;
int t, n, y[MaxN*2], ans;
bool type[MaxN*2]; // 1 for traveller, 0 for exit
set<int> s;
set<int> :: iterator it;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = 1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	t = Read(), n = Read();
	for(int i=1; i<=n; i++){
		int a = Read(), b = Read();
		type[a] = 1;
		y[a] = b;
	}
	for(int i=1; i<=n; i++){
		int c = Read(), d = Read();
		type[c] = 0;
		y[c] = d;
	}
	for(int i=0; i<2*n; i++){
		if(type[i] == 1) s.insert(y[i]);
		else{
			it = s.lower_bound(y[i]);
			if(it == s.begin()) continue;
			it--, ans++;
			s.erase(it);
		}
	}
	printf("%lld", ans);
	return 0;
}