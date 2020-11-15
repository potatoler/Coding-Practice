#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, ans;
char s[MaxN], t[MaxN];
queue<int> pos;

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
	n = Read();
	scanf("%s%s", s+1, t+1);
	for(int i=1; i<=n; i++)
		if(s[i] == '1') pos.push(i);
	for(int i=1; i<=n; i++){
		if(s[i] == t[i]){
			if(s[i] == '1') pos.pop();
			continue;
		}
		else if(s[i] == '1' && t[i] == '0'){
			if(pos.empty()){
				printf("-1");
				return 0;
			}
			int p1 = pos.front();
			pos.pop();
			if(pos.empty()){
				printf("-1");
				return 0;
			}
			int p2 = pos.front();
			pos.pop();
			ans += (p2 - p1);
			s[p1] = s[p2] = '0';
		}
		else if(s[i] == '0' && t[i] == '1'){
			if(pos.empty()){
				printf("-1");
				return 0;
			}
			int p = pos.front();
			pos.pop();
			ans += (p - i);
			s[p] = '0', s[i] = '1';
		}
	}
	printf("%lld", ans);
	return 0;
}