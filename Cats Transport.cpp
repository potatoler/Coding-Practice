#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<deque>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, p, dist[MaxN], t[MaxN], sum[MaxN], f[102][MaxN];
deque<int> q;

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

inline int Slope(int i, int k){
	return f[i-1][k] + sum[k];
}

signed main(){
	n = Read(), m = Read(), p = Read();
	for(int i=2; i<=n; i++)
		dist[i] = dist[i-1] + Read();
	for(int i=1; i<=m; i++){
		int h = Read(), tm = Read();
		t[i] = tm - dist[h];
	}
	sort(t+1, t+1+m);
	for(int i=1; i<=m; i++){
		sum[i] = sum[i-1] + t[i];
		f[0][i] = LLONG_MAX;
	}
	for(int i=1; i<=p; i++){
		while(!q.empty()) q.pop_front();
		for(int j=0; j<=m; j++){
			while(q.size() > 1 && Slope(i,q[1]) - Slope(i,q[0]) <= t[j] * (q[1]-q[0])) q.pop_front();
			if(!q.empty()) f[i][j] = Slope(i,q[0]) + t[j] * (j-q[0]) - sum[j];
			while(q.size() > 1 && (Slope(i,j)-Slope(i,q[q.size()-1])) * (q[q.size()-1]-q[q.size()-2]) <= (Slope(i,q[q.size()-1])-Slope(i,q[q.size()-2])) * (j-q[q.size()-1])) q.pop_back();
			q.push_back(j);
		}
	}
	printf("%lld", f[p][m]);
	return 0;
}