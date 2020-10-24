#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<climits>
#define int long long
#define ull unsigned long long
#define fake false
using namespace std;
const int MaxN = 200005, base = 19260817;
int n, m, nxt[MaxN][26], pos[26];
char str[MaxN];
ull hsh[MaxN][26], f[MaxN];

inline void Init(){
	f[0] = 1;
	for(int i=1; i<=n; i++){
		f[i] = f[i-1] * base;
		for(int j=0; j<26; j++){
			hsh[i][j] = (hsh[i-1][j] * base + (str[i] == char(j+'a')));
		}
	}
	for(int i=0; i<26; i++){
		pos[i] = n+1;
	}
	for(int i=n; i>=1; i--){
		pos[str[i] - 'a'] = i;
		for(int j=0; j<26; j++){
			nxt[i][j] = pos[j];
		}
	}
	return;
}

inline ull GetHash(int l, int r, int letter){
	return hsh[r][letter] - hsh[l-1][letter] * f[r-l+1];
}

inline bool Judge(int x, int y, int len , int letter){
	int p = nxt[x][letter];
	if(p > x+len-1) return true;
	p += y-x;
	return GetHash(x, x+len-1, letter) == GetHash(y, y+len-1, str[p]-'a');
}

inline bool Check(int x, int y, int len){
	for(int i=0; i<26; i++){
		if(!Judge(x, y, len, i)) return false;
	}
	return true;
}

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
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);
	n = Read(), m = Read();
	scanf("%s", str+1);
	Init();
	while(m--){
		int x = Read(), y = Read(), len = Read();
		if(Check(x, y, len)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}