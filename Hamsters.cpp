#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 202, MaxM = 100005;
string str[MaxN];
int n, m, len[MaxN], t, nxt[MaxN][MaxM];
struct Matrix{
	int a[MaxN][MaxN];
}ans, a;

Matrix operator * (Matrix x, Matrix y){
	Matrix res;
	for(int i=0; i<=n; i++)
		for(int j=0; j<=n; j++)
			res.a[i][j] = LLONG_MAX/2;	
	for(int i=0; i<=n; i++)
		for(int k=0; k<=n; k++)	
			for(int j=0; j<=n; j++)
				res.a[i][j] = min(res.a[i][j], x.a[i][k] + y.a[k][j]);
	return res;
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

inline void KMP(){
	a.a[0][0] = LLONG_MAX/2;
	for(int i=1; i<=n; i++){
		a.a[0][i] = len[i];
		a.a[i][0] = LLONG_MAX/2;
	}
	for(int k=1; k<=n; k++){
		int j=0;
		for(int i=2; i<=len[k]; i++){
			while(j > 0 && str[k][j+1] != str[k][i]) j = nxt[k][j];
			if(str[k][j+1] == str[k][i]) j++;
			nxt[k][i] = j;
		}
	}
	for(int k=1; k<=n; k++){
		for(int l=1; l<=n; l++){
			int j=0;
			for(int i=2; i<=len[k]; i++){
				while(j > 0 && str[l][j+1] != str[k][i]) j = nxt[l][j];
				if(str[l][j+1] == str[k][i]) j++;
				if(i == len[k]) a.a[k][l] = len[l] - j;
			}
		}
	}
	return;
}

inline void QuickPower(){
	for(int i=0; i<=n; i++)
		for(int j=0; j<=n; j++)
			ans.a[i][j] = a.a[i][j];
	m--;
	while(m){
		if(m & 1) ans = ans * a;
		a = a * a;
		m>>=1;
	}
	return;
}

inline bool Check(){
	for(int i=1; i<=n; i++)
		if(len[i] == 1) return true;
	return false;
}

signed main(){
	n = Read(), m = Read();
	if(!m){
		printf("0");
		return 0;
	}
	for(int i=1; i<=n; i++){
		cin >> str[i];
		len[i] = str[i].size();
		str[i] = ' ' + str[i];
	}
	if(Check()){
		printf("%lld", m);
		return 0;
	}
	KMP();
	QuickPower();
	int answer = LLONG_MAX/2;
	for(int i=1; i<=n; i++)
		answer = min(answer, ans.a[0][i]);
	printf("%lld", answer);
	return 0;
}