#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102, MaxM = 4503;
int n, m;
int dis[MaxN][MaxN], cnt[MaxN][MaxN][MaxN];
double I[MaxN];

inline int Read() {
	int num = 0, op = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	int n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
		cnt[u][v][0] = cnt[v][u][0] = 1;
	}
	for(int i=1; i<=n; i++)
		dis[i][i] = 0;
	for(int k=1; k<=n; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(k == i || k == j || i == j) continue;
				if(dis[i][k] + dis[k][j] > dis[i][j]) continue;
				else if(dis[i][k] + dis[k][j] == dis[i][j]){
					cnt[i][j][0] += cnt[i][k][0] * cnt[k][j][0];;
//					cnt[j][i][0] += cnt[i][k][0] * cnt[k][j][0];;
				}
				else{
					dis[i][j] = dis[i][k] + dis[k][j];
					cnt[i][j][0] = cnt[i][k][0] * cnt[k][j][0];
				}
			}
		}
	}
	for(int o=1; o<=n; o++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(i == o || j == o || i == j) continue;
				if(dis[i][o] + dis[o][j] == dis[i][j]){
					cnt[i][j][o] = cnt[i][o][0] * cnt[o][j][0];
				}
			}
		}
	}
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=n; j++){
//			printf("%lld ", cnt[i][j][3]);
//		}
//		printf("\n");
//	}
	for(int o=1; o<=n; o++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(i == o || j == o || i == j) continue;
				I[o] += (double)cnt[i][j][o] / (double)cnt[i][j][0];
			}
		}
		printf("%.3f\n", I[o]);
	}
	return 0;
}