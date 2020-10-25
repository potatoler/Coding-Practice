#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
#define lowbit(x) x&(-x)
using namespace std;
const int MaxN = 55, MaxM = (1<<20)+10;
double f[MaxM];
int n, m, s[MaxN][MaxN], sta[MaxM], bit[MaxN], rm[MaxM], siz[MaxM];

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

signed main() {
	n = Read(), m = Read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) s[i][j] = Read();
	for (int i = 0; i < m; i++) rm[1ll << i] = i;
	int all = (1ll << m) - 1;
	for (int i = 1; i <= n; i++) {
		memset(bit, 0, sizeof(bit));
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++)
				if (s[i][k] == s[j][k])
					bit[k] |= 1ll << (j - 1);
		siz[0]++;
		sta[0] = (1ll << n) - 1;
		for (int j = 1; j <= all; j++) {
			int t = lowbit(j);
			sta[j] = sta[j - t] & bit[rm[t] + 1];
			if (sta[j] != (1ll << (i - 1)))
				siz[j]++;
		}
	}
	for (int j = all; j >= 0; j--) {
		if (!siz[j])
			continue;
		int sz = 0;
		for (int k = 1; k <= m; k++) {
			if ((1ll << (k - 1)) & j)
				continue;
			int t = j | (1ll << (k - 1));
			f[j] += siz[t] * f[t];
			sz++;
		}
		f[j] = f[j] / ((double)sz * siz[j]) + 1;
	}
	printf("%.5lf", f[0]);
	return 0;
}