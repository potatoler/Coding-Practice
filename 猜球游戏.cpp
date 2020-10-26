#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, a[MaxN], b[MaxN];
struct Array{
	int pos[10];
	
	inline void Init(){
		for(int i=0; i<10; i++)
			pos[i] = i;
		return;
	}
	
	inline Array operator - (const Array &o) const{
		Array res, tmp;
		for(int i=0; i<10; i++)
			tmp.pos[o.pos[i]] = i;
		for(int i=0; i<10; i++)
			res.pos[i] = tmp.pos[pos[i]];
		return res;
	}
}sum[MaxN];

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

inline Array Query(int l, int r){
	Array res;
	for(int i=0; i<10; i++)
		res.pos[i] = i;
	for(int i=l; i<=r; i++)
		swap(res.pos[a[i]], res.pos[b[i]]);
	return res;
}

signed main(){
//	freopen("b.in", "r", stdin);
//	freopen("b.out", "w", stdout);
	for(int i=0; i<MaxN; i++)
		sum[i].Init();
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read(), b[i] = Read();
		sum[i] = sum[i-1];
		swap(sum[i].pos[a[i]], sum[i].pos[b[i]]);
	}
	while(m--){
		int l = Read(), r = Read();
		Array ans = sum[r] - sum[l-1];
		for(int i=0; i<10; i++)
			printf("%lld ", ans.pos[i]);
		printf("\n");
	}
	return 0;
}