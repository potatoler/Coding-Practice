#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int Mod = 1000000007;
int n, b, k, x;
struct Matrix{
	int a[102][102];
	Matrix operator * (const Matrix &y) const;
}A,I;

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

inline Matrix QuickPower(int p){
	Matrix res = I;
	while(p){
		if(p & 1) res = res * A;
		A = A * A;
		p >>= 1;
	}
	return res;
}

signed main(){
	n = Read(), b = Read(), k = Read(), x = Read();
	for(int i=0; i<x; i++)
		I.a[i][i] = 1;
	for(int i=0; i<n; i++){
		int w = Read();
		for(int j=0; j<x; j++){
			A.a[j][(j*10%x + w%x) % x]++;
		}
	}
	Matrix ans = QuickPower(b);
	printf("%lld", ans.a[0][k]);
	return 0;
}

Matrix Matrix::operator * (const Matrix &y) const {
	Matrix res;
	for(int i=0; i<x; i++){
		for(int j=0; j<x; j++){
			res.a[i][j] = 0;
			for(int l=0; l<x; l++){
				res.a[i][j] = (res.a[i][j] + a[i][l] * y.a[l][j] % Mod) % Mod;
			}
		}
	}
	return res;
}