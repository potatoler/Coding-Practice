#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005*10;
int n, ans, sum[MaxN], trie[MaxN][26], cnt;
char str[105];
vector<int> storage[MaxN];

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

inline void Insert(char s[], int val, int serial){
	int len = strlen(s+1), pos = 0;
	for(int i=1; i<=len; i++){
		int cur = s[i] - 'a';
		if(!trie[pos][cur]) trie[pos][cur] = ++cnt;
		pos = trie[pos][cur];
		sum[pos] += val;
		if(sum[pos] > storage[pos].size()) storage[pos].push_back(serial);
	}
	return;
}

inline int Query(char s[], int lim){
	int len = strlen(s+1), pos = 0;
	for(int i=1; i<=len; i++){
		int cur = s[i] - 'a';
		pos = trie[pos][cur];
		if(storage[pos].size() <= lim) return -1;
	}
	return storage[pos][lim];
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		int op = Read();
		scanf("%s", str+1);
		if(op == 1) Insert(str, 1, i);
		else if(op == 2) Insert(str, -1, i);
		else{
			int a = Read(), b = Read(), c = Read();
			int lim = (a * abs(ans) + b) % c;
			ans = Query(str, lim);
			printf("%lld\n", ans);
		}
	}
	return 0;
}