#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
double f[110][110][110], rwin = 0.0, swin = 0.0, qwin = 0.0;
int r, s, q, tot;

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
	r = Read(), s = Read(), q = Read();
	f[r][s][q]=1.0;
	for(int i=r; i>=0; i--)
	for(int j=s; j>=0; j--)
	for(int k=q; k>=0; k--){
		tot = i*j + j*k + k*i;
		if(i && k) f[i-1][j][k] += 1.0 * f[i][j][k] * k * i / tot;
		if(j && i) f[i][j-1][k] += 1.0 * f[i][j][k] * i * j / tot;
		if(k && j) f[i][j][k-1] += 1.0 * f[i][j][k] * j * k / tot;
		if(!j && !k && i) rwin += f[i][j][k];
		if(!i && !k && j) swin += f[i][j][k];
		if(!i && !j && k) qwin += f[i][j][k];
	}
	printf("%.9lf %.9lf %.9lf", rwin, swin, qwin);
}