#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int MaxM = 7100006;
int n, m, q, u, v, t, a[MaxM], ans[MaxM], s=0, y=0, tot=0;
queue<int> q1, q2, q3;

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

inline void Write(int x){
	if(x < 0) printf("-"), x=-x;
	if(x > 9) Write(x/10);
	putchar(x % 10 + '0');
	return;
}

int GetMax(){
	int x1 = -(1<<30), x2 = x1, x3 = x1;
	if(!q1.empty()) x1 = q1.front();
	if(!q2.empty()) x2 = q2.front();
	if(!q3.empty()) x3 = q3.front();
	if(x1 >= x2 && x1 >= x3){
		q1.pop();
		return x1;
	}
	else if(x2 >= x1 && x2 >= x3){
		q2.pop();
		return x2;
	}
	q3.pop();
	return x3;
}

void Put(int x1, int x2){
	if(x1 < x2){
		int z=x1;
		x1 = x2, x2 = z;
	}
	q2.push(x1);
	q3.push(x2);
	return;
}

bool cmp(int x,int y){
	return x>y;
}

signed main(){
	n = Read(), m = Read(), q = Read(), u = Read(), v = Read(), t = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	sort(a+1, a+n+1, cmp);
	for(int i=1; i<=n; i++)
		q1.push(a[i]);
	for(int i=1; i<=m; i++){
		ans[i] = GetMax() + y;
		int j = ans[i] * u / v, k = ans[i] - j;
		y += q;
		Put(j-y,k-y);
	}
	while(!q1.empty() || !q2.empty() || !q3.empty())
		a[++tot] = GetMax() + y;
	for(int i=t; i<=m; i+=t)
		Write(ans[i]), putchar(' ');
	putchar('\n');
	for(int i=t; i<=tot; i+=t)
		Write(a[i]), putchar(' ');
	putchar('\n');
	return 0;
}