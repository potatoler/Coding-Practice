#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
#define int long long
const int Mod = 1000000007;
int x, n, sum;
multiset<int> ms;
multiset<int>::iterator it_ms;
set<int> s;
set<int>::iterator it_s;
map<int,int> mp;

inline int Read(){
	int num = 0, op = 1;
	char ch= getchar();
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

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

signed main() {
	n = Read(), x = Read();
	for(int i=1;i<=n;++i){
		int v = Read();
		sum+=v;
		ms.insert(v);
	}
	for(it_ms = ms.begin(); it_ms != ms.end(); it_ms++){
		++mp[sum-*it_ms];
		s.insert(sum-*it_ms);
	}
	for(it_s = s.begin(); it_s != s.end(); it_s++){
		if(mp[*it_s] >= x){
			mp[(*it_s)+1] += mp[*it_s] / x;
			mp[*it_s] %= x;
			ms.insert((*it_s)+1), s.insert((*it_s)+1);
		}
	}
	for(it_s = s.begin(); it_s != ms.end(); it_s++){
		if(mp[*it_s]){
			printf("%lld\n", QuickPower(x,min(sum,*it_s)));
			return 0;
		}
	}
	return 0;
}