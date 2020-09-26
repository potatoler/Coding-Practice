#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int MaxN = 50004, MaxM = 200005, MaxS = 1000006;
int n, m, length, a[MaxN], ans[MaxM], cnt[MaxS];
int p = 0, q = 1, res;
struct Query{
	int l, r, serial;
}query[MaxM];

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

inline int Locate(int x){
	return x / length;
}

inline bool cmp(const Query &a, const Query &b){
	int posa = Locate(a.l), posb = Locate(b.l);
	if(posa != posb) return posa < posb;
	return a.r < b.r;
}

inline void Add(int x, int &res){
	if(!cnt[x]) res++;
	cnt[x]++;
	return;
}

inline void Remove(int x, int &res){
	cnt[x]--;
	if(!cnt[x]) res--;
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	m = Read();
	length = sqrt((double)n * n / m);
	for(int i=1; i<=m; i++){
		query[i].l = Read(), query[i].r = Read();
		query[i].serial = i;
	}
	sort(query+1, query+1+m, cmp);
	for(int i=1; i<=m; i++){
		int serial = query[i].serial, l = query[i].l, r = query[i].r;
		while(p<r) Add(a[++p], res);
		while(p>r) Remove(a[p--], res);
		while(q<l) Remove(a[q++], res);
		while(q>l) Add(a[--q], res);
		ans[serial] = res;
	}
	for(int i=1; i<=m; i++)
		printf("%d\n", ans[i]);
	return 0;
}