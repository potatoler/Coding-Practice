#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#include<map>
#define int long long
using namespace std;
int n, k, ans;
map< vector< pair<int,int> >, int> mp;

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

inline void Divide(int x, vector< pair<int,int> > &tmp){
	for(int i=2; i<=sqrt(x); i++){
		int cnt = 0;
		while(x % i == 0){
			cnt++;
			x /= i;
		}
		cnt %= k;
		if(cnt) tmp.push_back(make_pair(i, cnt));
	}
	if(x != 1) tmp.push_back(make_pair(x, 1));
	return;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		int a = Read();
		vector< pair<int,int> > tmp;
		Divide(a, tmp);
		ans += mp[tmp];
		for(int j=0; j<tmp.size(); j++) tmp[j].second = k - tmp[j].second;
		mp[tmp]++;
	}
	printf("%lld", ans);
}