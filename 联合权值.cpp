#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 10007;
int n, cntEdge, head[MaxN], value[MaxN], sumValue, maxValue;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	for(int i=1; i<=n; i++)
		value[i] = Read();
	for(int i=1; i<=n; i++){
		int max1 = 0, max2 = 0;
		int square_of_sum = 0, sum_of_square = 0;
		for(int j = head[i]; j; j = edge[j].nextEdge){
			int des = edge[j].destination;
			if(value[des] > max1) max2 = max1, max1 = value[des];
			else if(value[des] > max2) max2 = value[des];
			square_of_sum = (square_of_sum + value[des]) % Mod;
			sum_of_square = (sum_of_square + value[des] * value[des]) % Mod;
		}
		square_of_sum = square_of_sum * square_of_sum % Mod;
		sumValue = (sumValue + square_of_sum + Mod - sum_of_square) % Mod;
		maxValue = max(maxValue, max1*max2);
	}
	printf("%lld %lld", maxValue, sumValue);
}