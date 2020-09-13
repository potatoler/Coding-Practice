#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<random>
#define int long long
using namespace std;
const int MaxN = 102;
int n, m, fa[MaxN];
bool in[MaxN];
char s[MaxN], q[MaxN], hate[6][30];

inline void Rand(){
	memset(in, 0, sizeof(in));
	in[0] = 1;
	for(int i=1; i<=n; i++){
		int cur = rand() % (n-i+1) + 1;
		int j = 1;
		while(cur -= !in[j])
			j++;
		while(!in[fa[j]])
			j = fa[j];
		in[j] = 1;
		q[i] = s[j];
	}
}

signed main(){
	scanf("%lld", &n);
	for(int i=1; i<=n; i++)
		scanf("%lld", &fa[i]);
	scanf("%s", s+1);
	scanf("%lld", &m);
	for(int i=1; i<=m; i++)
		scanf("%s", hate[i]+1);
	int cnt = 0, round = 10000;
	while(round--){
		Rand();
		bool prob = 0;
		for(int i=1; i<=m; i++){
			int len = strlen(hate[i]+1);
			for(int j=1; j<=n-len+1; j++){
				int k=0;
				while(k<len && q[j+k] == hate[i][k+1]) k++;
				if(k == len){
					prob = 1;
					break;
				}
			}
			if(prob) break;
		}
		cnt += prob;
	}
	printf("%lf", 1-(double)cnt/10000.0);
	return 0;
}