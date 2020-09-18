#pragma optimize(3)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, m, q, dist[MaxN], gcd[MaxN], father[MaxN];

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

inline int GCD(int a, int b){
	if(!b) return a;
	return GCD(b, a%b);
}

inline int Get(int x){
	if(x == father[x]) return x;
	int root = Get(father[x]);
	dist[x] = (dist[x] + dist[father[x]]) % m;
	return father[x] = root;
}

inline void ExGCD(int a, int b, int &x, int &y){
	if(b == 0) x = 1, y = 0;
	else{
		ExGCD(b, a%b, y, x);
		y -= a / b * x;
	}
	return;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=n; i++)
		father[i] = i, gcd[i] = m;
	for(int i=1; i<=q; i++){
		int op = Read(), u = Read(), v = Read(), w = Read();
		int fu = Get(u), fv = Get(v);
		if(op == 1){
			if(fu != fv){
				father[fu] = fv;
				dist[fu] = (dist[u] + dist[v] + w) % m;
				gcd[fv] = GCD(GCD(gcd[fu], gcd[fv]), 2*w);
			}
			else gcd[fu] = GCD(GCD(gcd[fu], ((dist[u] + dist[v] + w) % m)), 2*w);
		}
		else{
			int ans = 0, b = Read() % gcd[fu], c = Read();
			if(fu != fv){
				printf("0\n");
				continue;
			}
			int A = b, B = gcd[fu], G = GCD(A,B), C = dist[u] + dist[v] - w + B;
			// printf("%lld %lld %lld %lld\n", A, B, G, C);
			if(C%G){
				printf("0\n");
				continue;
			}
			int x, y;
			A /= G, B /= G, C /= G;
			ExGCD(A,B,x,y);
			x = (x * C % B + B) % B;
			// printf("%lld %lld\n", x, y);
			if(x < c) ans = (c-1-x) / B + 1;
			printf("%lld\n", ans);
			// if(!ans) printf(" azhe\n");
			// else printf("\n");
		}
	}
	return 0;
}