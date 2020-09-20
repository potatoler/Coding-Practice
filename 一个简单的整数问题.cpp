#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define LL long long
using namespace std;
const int MaxN = 100005, SqrtN = 403;
int n, m, len;
LL add[SqrtN], sum[SqrtN], value[MaxN];

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
	return x / len;
}

inline void Change(int l, int r, int w){
	if(Locate(l) == Locate(r)) {
		for(int i=l; i<=r; i++){
			value[i] += w;
			sum[Locate(i)] += w;
		}
	}
	else{
		int i = l, j = r;
		while(Locate(i) == Locate(l)){
			value[i] += w;
			sum[Locate(i)] += w;
			i++;
		}
		while(Locate(j) == Locate(r)){
			value[j] += w;
			sum[Locate(j)] += w;
			j--;
		}
		for(int k = Locate(i); k <= Locate(j); k++){
			sum[k] += len * w;
			add[k] += w;
		}
	}
}

inline LL Query(int l, int r){
	LL ans = 0;
	if(Locate(l) == Locate(r)){
		for(int i=l; i<=r; i++)
			ans += value[i] + add[Locate(i)];
	}
	else{
		int i = l, j = r;
		while(Locate(i) == Locate(l)){
			ans += value[i] + add[Locate(i)];
			i++;
		}
		while(Locate(j) == Locate(r)){
			ans += value[j] + add[Locate(j)];
			j--;
		}
		for(int k=Locate(i); k<=Locate(j); k++)
			ans += sum[k];
	}
	return ans;
}

signed main(){
	n = Read(), m = Read();
	len = sqrt(n);
	for(int i=1; i<=n; i++){
		value[i] = Read();
		sum[Locate(i)] += value[i];
	}
	char op[2];
	while(m--){
		scanf("%s", op);
		int l = Read(), r = Read();
		if(op[0] == 'C'){
			LL w = Read();
			Change(l, r, w);
		}
		else printf("%lld\n", Query(l, r));
	}
	return 0;
}