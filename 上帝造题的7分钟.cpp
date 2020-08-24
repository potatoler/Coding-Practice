#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
//#define int long long
#define LowBit(x) (x & -x)
using namespace std;
const int MaxN = 3000;
int n, m;
int tree[5][MaxN][MaxN];

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

inline void Add(int x, int y, int k){
	for(int i=x; i<=n;i += LowBit(i))
		for(int j=y; j<=m; j += LowBit(j)){
			tree[1][i][j] += k;
			tree[2][i][j] += k * (x-1);
			tree[3][i][j] += k * (y-1);
			tree[4][i][j] += k * (x-1) * (y-1);
		}
}

inline int Ask(int x, int y){
	int ans[5] = {0,0,0,0,0};
	for(int i=x; i; i -= LowBit(i))
		for(int j=y; j; j -= LowBit(j)){
			ans[1] += tree[1][i][j];
			ans[2] += tree[2][i][j];
			ans[3] += tree[3][i][j];
			ans[4] += tree[4][i][j];
		}
	return ans[1]*x*y - ans[2]*y - ans[3]*x + ans[4];
}

signed main(){
	n = Read(), m = Read();
	char op;
	while(cin>>op){
		int a = Read(), b = Read(), c = Read(), d = Read();
		if(op == 'L'){
			int delta = Read();
			Add(c+1, d+1, delta);
			Add(c+1, b, -delta);
			Add(a, d+1, -delta);
			Add(a, b, delta);
		}
		else printf("%d\n", Ask(c, d) - Ask(c, b-1) - Ask(a-1, d) + Ask(a-1, b-1));
	}
	return 0;
}