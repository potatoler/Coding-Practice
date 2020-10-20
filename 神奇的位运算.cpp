#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;
const int MaxN = 502;
int n, m, t;
char str[MaxN][MaxN];

inline int Read(){
	int num = 0, opt = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') opt = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * opt;
}

signed main(){
	t = Read();
	while(t--){
		n = Read(), m = Read();
		for(int i=1; i<=n; i++)
			scanf("%s", str[i]+1);
		int ans = 0;
		for(int i=1; i<=m; i++){
			if(ans >= 2) break;
			int cnt[2] = {0,0};
			for(int j=1; j<=n; j++) cnt[str[j][i] - '0']++;
			if (cnt[1] == 0 && cnt[0] == 0) ans = 3;
			if (cnt[1] == 0 && cnt[0]) ans = 2;
			if (cnt[1] == 1 && cnt[0] == 0) ans = 2;
			if (cnt[1] == 1 && cnt[0]) ans = 1;
			if (cnt[1] >= 2 && cnt[0] == 0) ans = 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}