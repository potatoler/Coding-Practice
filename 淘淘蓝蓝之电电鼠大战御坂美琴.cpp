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
const int MaxN = 100000008;
int d[MaxN], a[MaxN];
struct Pair{
	int v, w;    
};

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
	int i, j, n, V, num;
	num = Read(), V = Read(), n = Read();
	if (n == 0 || V == 0) return 0;
	int v;
	int w;
	int s;
	vector<struct Pair> good;
	struct Pair * temp;
	for(i=1; i<=n; i++){
		d[i] = Read();
	}
	for(i=1; i<=n; i++){
		a[i] = Read();
	}
	for (i = 1; i <= n; i++){
		s = a[i], v = w = d[i];
		for (j = 1; j <= s; s-= j, j *= 2){
			temp = new Pair();
			temp->v = v * j; 
			temp->w = w * j; 
			good.push_back(*temp);
		} 
		if (s != 0)
		{
			temp = new Pair();
			temp->v = v * s;
			temp->w = w * s; 
			good.push_back(*temp);            
		} 
	}
	n = good.size();
	vector<int> f(V + 1, 0);
	for (i = 1; i <= n; i++){
		for (j = V; j >= good[i - 1].v; j--){
			if (good[i - 1].v <= j)
				f[j] = max(f[j], f[j - good[i - 1].v] + good[i - 1].w);
		}
	}
	cout << f[V] << endl;
	return 0;
}