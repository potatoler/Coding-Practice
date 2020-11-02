#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<stack>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200005;
int res[30][30], n, m, q, c[MaxN];
int father[MaxN];

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

inline bool Judge(stack<int> hu, queue<int> ka){
	while(true){
		int hh = hu.top(), kk = ka.front();
		if(res[kk][hh]) hu.pop();
		else ka.pop();
		if(hu.empty()) return true; // kage wins
		if(ka.empty()) return false; // hutsu wins
	}
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=m; i++){
		for(int j=1; j<=m; j++){
			res[i][j] = Read();
		}
	}
	for(int i=1; i<=n; i++)
		c[i] = Read();
	for(int i=1; i<n; i++){
		int x = Read(), y = Read();
		father[y] = x;
	}
	while(q--){
		int k = Read(), p = Read();
		queue<int> kage;
		for(int i=1; i<=k; i++){
			int w = Read();
			kage.push(w);
		}
		stack<int> hutsu;
		while(p != 0){
			hutsu.push(c[p]);
			p = father[p];
		}
		int keko = Judge(hutsu, kage);
		if(keko) printf("1\n");
		else printf("0\n");
	}
	return 0;
}