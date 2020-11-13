#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 10004;
int n, m, ans;
char s[MaxN];
vector<int> column[MaxN];

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
	for(int i=1; i<=m; i++){
		scanf("%s", s+1);
		int ch = s[1], cnt = 0, len = strlen(s+1)+1;
//		printf("%lld\n", len);
		for(int j=2; j<=len; j++){
			if(s[j] == ch) cnt++;
			else{
				column[i].push_back(cnt);
				ch = s[j];
				cnt = 0;
			}
		}
	}
//	for(int i=1; i<=m; i++){
//		printf("%lu: ", column[i].size());
//		for(int j=0; j<column[i].size(); j++){
//			printf("%lld ", column[i][j]);
//		}
//		printf("\n");
//	}
	for(int i=1; i<=m; i++){
		int len = column[i].size(), mid = len / 2;
		int c1 = INT_MAX, c2 = INT_MAX;
		for(int j=mid; j>=0; j--){
			if(column[i][j]){
				c1 = j;
				break;
			}
		}
		for(int j=mid; j<len; j++){
			if(column[i][j]){
				c2 = j;
				break;
			}
		}
//		printf("%lld %lld\n", c1, c2);
		if(c1 == INT_MAX && c2 == INT_MAX) continue;
		if(c2 == INT_MAX){
			int cnt = 1;
			for(int j=c1; j<len; j++)
				if(!column[i][j]) cnt++;
			ans += cnt;
		}
		else if(c1 == INT_MAX){
			int cnt = 1;
			for(int j=c2; ~j; j--)
				if(!column[i][j]) cnt++;
			ans += cnt;
		}
		else ans += max(c2-c1+1, mid+1);
	}
	printf("%lld", ans);
	return 0;
}