#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int n;
double xba, ans, a[10][10], sum[10][10], f[20][10][10][10][10];
#define cur f[k][x][y][xx][yy]

inline double Read(){
	double num = 0, op = 1;
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


inline double GetValue(int x, int y, int xx, int yy){
	double s = sum[xx][yy] - sum[xx][y-1] - sum[x-1][yy] + sum[x-1][y-1];
	return s*s / n;
}

signed main(){
	n = Read();
	for(int i=1; i<=8; i++)
		for(int j=1; j<=8; j++)
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + Read();
	double xba = sum[8][8] / n;
	for(int k=1; k<=n; k++){
		for(int x=1; x<=8; x++){
			for(int y=1; y<=8; y++){
				for(int xx=1; xx<=8; xx++){
					for(int yy=1; yy<=8; yy++){
						cur = INT_MAX;
						if(k == 1){
							cur = GetValue(x, y, xx, yy);
							continue;
						}
						for(int i=x; i<xx; i++){
							cur = min(cur, f[k-1][x][y][i][yy] + GetValue(i+1, y, xx, yy));
							cur = min(cur, f[k-1][i+1][y][xx][yy] + GetValue(x, y, i, yy));
						}
						for(int i=y; i<yy; i++){
							cur = min(cur, f[k-1][x][y][xx][i] + GetValue(x, i+1, xx, yy));
							cur = min(cur, f[k-1][x][i+1][xx][yy] + GetValue(x, y, xx, i));
						}
					}
				}
			}
		}
	}
	ans = sqrt(f[n][1][1][8][8] - xba*xba);
	printf("%.3lf", ans);
	return 0;
}