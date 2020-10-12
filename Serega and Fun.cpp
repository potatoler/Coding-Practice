#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
const int MaxN = 100005, MaxB = 333;
int n, m, tms[MaxB][MaxN], value[MaxN], belong[MaxN], cntBlock, len, l[MaxN], r[MaxN], lastans;
deque<int> dq[MaxB];

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

inline void Init(){
	len = sqrt(n);
	cntBlock = n / len;
	if(n&len) cntBlock++;
	for(int i=1; i<=n; i++)
		belong[i] = (i-1) / len + 1;
	for(int i=1; i<=cntBlock; i++){
		l[i] = (i-1) * len + 1;
		r[i] = i * len;
	}
	r[cntBlock] = n;
	for(int i=1; i<=cntBlock; i++){
		for(int j=l[i]; j<=r[i]; j++){
			tms[i][value[j]]++;
			dq[i].push_back(value[j]);
		}
	}
	return;
}

inline void Change(int x,int y){
	if(belong[x] == belong[y]){
		int serial = belong[x];
		x -= l[serial];
		y -= l[serial];
		int last = dq[serial][y];
		for(int i=y; i>x; i--)
			dq[serial][i] = dq[serial][i-1];
		dq[serial][x] = last;
		return;
	}
	int last = dq[belong[y]][y-l[belong[y]]];
	int first = dq[belong[x]][r[belong[x]]-l[belong[x]]];
	tms[belong[x]][first]--;
	tms[belong[y]][last]--;
	for(int i = r[belong[x]]; i > x; i--)
		dq[belong[x]][i-l[belong[x]]] = dq[belong[x]][i-l[belong[x]]-1];
	dq[belong[x]][x-l[belong[x]]] = last;
	tms[belong[x]][last]++;
	for(int i = belong[x]+1; i < belong[y]; i++){
		int tmp = first;
		tms[i][first]++;
		first = dq[i][r[i]-l[i]];
		dq[i].pop_back();
		dq[i].push_front(tmp);
		tms[i][first]--;
	}
	for(int i=y; i > l[belong[y]]; i--)
		dq[belong[y]][i-l[belong[y]]] = dq[belong[y]][i-l[belong[y]]-1];
	dq[belong[y]][0] = first;
	tms[belong[y]][first]++;
}

inline int Query(int x,int y,int k){
	int ans = 0;
	if(belong[x] == belong[y]){
		for(int i=x; i<=y; i++)
			if(dq[belong[x]][i-l[belong[x]]] == k) ans++;
		return ans;
	}
	for(int i=x; i <= r[belong[x]]; i++)
		if(dq[belong[x]][i-l[belong[x]]] == k) ans++;
	for(int i = belong[x]+1; i < belong[y]; i++)
		ans += tms[i][k];
	for(int i = l[belong[y]]; i<=y; i++)
		if(dq[belong[y]][i-l[belong[y]]] == k) ans++;
	return ans;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		value[i] = Read();
	Init();
	m = Read();
	while(m--){
		int op = Read(), x = Read(), y = Read();
		x = (x + lastans - 1) % n + 1;
		y = (y + lastans - 1) % n + 1;
		if(x > y) swap(x,y);
		if(op == 1) Change(x,y);
		else{
			int k = Read();
			k = (k + lastans - 1) % n + 1;
			lastans = Query(x,y,k);
			printf("%d\n",lastans);
		}
	}
	return 0;
}

