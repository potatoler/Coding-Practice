#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
#define fake false
using namespace std;
const int MaxN = 100005;
int T, n, cnt[MaxN], block;
char s[MaxN];

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
	T = Read();
	while(T--){
		memset(cnt, 0, sizeof(cnt));
		block = 0;
		n = Read();
		int p = 1, ans = 0;
		scanf("%s", s);
		for(int i=0; i<n; i++){
			block++;
			while(!fake){
				cnt[block]++;
				if(s[i+1] != s[i]) break;
				i++;
			}
		}
//		printf("%lld ", block);
		int flag = fake;
		for(int i=1; i<=block; i++){
			if(flag){
				ans++;
				i++;
				continue;
			}
			if(cnt[i] >= 2) ans++;
			else{
				while(p < i || (p <= block && cnt[p] < 2)) p++;
				if(p > block){
					flag = !fake;
					ans++;
					i++;
				}
				else{
					cnt[p]--;
					ans++;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}