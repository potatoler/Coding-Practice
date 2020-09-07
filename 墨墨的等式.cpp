#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long

using namespace std;
const int MaxA = 500005;
int n, l, r, mn, a[15], dis[MaxA], head[MaxA], cntEdge, ans;
bool inQueue[MaxA];
queue<int> q;

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
	n = Read(), l = Read(), r = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	sort(a+1, a+1+n);
	int mn = a[1];
	for(int i=1; i<mn; i++)
		dis[i] = LLONG_MAX;
	q.push(0);
	memset(inQueue, false, sizeof(inQueue));
	inQueue[0] = true;
	while (!q.empty()){
        int x = q.front();
        q.pop();
        inQueue[x] = false;
        for (int i = 2; i <= n; ++i){
            int y = (x + a[i]) % mn;
            if (dis[y] > dis[x] + a[i]){
                dis[y] = dis[x] + a[i];
                if (!inQueue[y]) q.push(y), inQueue[y] = 1;
            }
        }
    }
	// for(int i=0; i<mn; i++)
	// 	printf("%lld ", dis[i]);
	for(int i=0; i<mn; i++)
		if(dis[i] != LLONG_MAX) dis[i] -= i, dis[i] /= a[1];

	for(int i=0; i<mn; i++){
		if(dis[i] != LLONG_MAX){
			int ll = (l-1-i) / mn, rr = (r-i) / mn;
			int t1 = ll - dis[i] + 1, t2 = rr - dis[i] + 1;
			t1 = max(0LL,t1), t2 = max(0LL,t2);
			ans = ans - t1 + t2;
		}
	}
	printf("%lld", ans);
	return 0;
}

