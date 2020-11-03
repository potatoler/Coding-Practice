#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<map>
#define int long long
using namespace std;
const int MaxN = 100005;
int T, n, k, a[MaxN], sum[MaxN];
map<int,int> record;

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
	freopen("perfume.in", "r", stdin);
	freopen("perfume.out", "w", stdout);
	T = Read();
	while(T--){
		n = Read(), k = Read();
		for(int i=1; i<=n; i++){	
			a[i] = Read();
			sum[i] = sum[i-1] + a[i];
		}
		int power = 1, ans = 0;
		while(abs(power) <= 1e14){
			record.clear();
			record[0] = 1;
			for(int i=1; i<=n; i++){
				if(record.count(sum[i] - power)) ans += record[sum[i] - power];
				record[sum[i]]++;
			}
			power *= k;
			if(power == 1) break;
		}
		printf("%lld\n", ans);
	}
	return 0;
}