#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1050000;
char s[MaxN], clip[MaxN];
int pre[MaxN], suf[MaxN], cnt[30], ans;

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

inline void StrCopy(int st, int ed){
	int pos = 1;
	while(st<=ed){
		clip[pos] = s[st];
		pos++, st++;
	}
	return;
}

inline bool OK(int len, int clen){
	for(int i=1, j=1; i<=len; i++, j++){
		if(j == clen+1) j = 1;
		if(s[i] != clip[j]) return false;
	}
	return true;
}

signed main(){
	freopen("string.in", "r", stdin);
	freopen("string.out", "w",stdout);
	int T = Read();
	while(T--){
		memset(pre, 0, sizeof(pre));
		memset(suf, 0, sizeof(suf));
		ans = 0;
		scanf("%s", s+1);
		int len = strlen(s+1);
		memset(cnt, 0, sizeof(cnt));
		for(int i=1; i<=len; i++){
			cnt[(s[i] - 'a')]++;
			for(int j=0; j<26; j++)
				if(cnt[j] & 1) pre[i]++;
		}
		memset(cnt, 0, sizeof(cnt));
		for(int i=len; i>=1; i--){
			cnt[(s[i] - 'a')]++;
			for(int j=0; j<26; j++){
				if(cnt[j] & 1) suf[len-i+1]++;
			}
		}
		for(int c=1; c<=len; c++){
			for(int ab=2; ab<=len-c; ab++){
				if((len-c) % ab) continue;
				StrCopy(1,ab);
				if(!OK(len-c, ab)) continue;
				for(int a=1; a<ab; a++){
//					printf("a = ");
//					for(int i=1; i<=a; i++)
//						printf("%c", s[i]);
//					printf("\n");
//					printf("b = ");
//					for(int i=a+1; i<=ab; i++)
//						printf("%c", s[i]);
//					printf("\n");
//					printf("c = ");
//					for(int i=len-c; i<=len; i++)
//						printf("%c", s[i]);
//					printf("\n");
//					printf("\n");
					if(pre[a] <= suf[c]) ans++;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
