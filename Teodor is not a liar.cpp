#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, a[MaxN], f[MaxN], g[MaxN], ans;
vector<int> number;

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
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int l = Read(), r = Read();
		a[l]++, a[r+1]--;
	}
	for(int i=1; i<=m; i++)
		a[i] += a[i-1];
	number.clear();
	number.push_back(a[1]);
	f[1] = 1;
	for(int i=2; i<=m; i++){
		if(a[i] >= number.back()){
			number.push_back(a[i]);
			f[i] = number.size();
		}
		else{
			int pos = upper_bound(number.begin(), number.end(), a[i]) - number.begin();
			number[pos] = a[i];
			f[i] = pos + 1;
		}
	}
	number.clear();
	number.push_back(a[m]);
	g[m] = 1;
	for(int i = m-1; i>=1; i--){
		if(a[i] >= number.back()){
			number.push_back(a[i]);
			g[i] = number.size();
		}
		else{
			int pos = upper_bound(number.begin(), number.end(), a[i]) - number.begin();
			number[pos] = a[i];
			g[i] = pos + 1;
		}
	}
	for(int i=1; i<=m; i++)
		ans = max(ans, f[i]+g[i]-1);
	printf("%lld", ans);
	return 0;
}