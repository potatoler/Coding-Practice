#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, a[MaxN], l[MaxN], r[MaxN], sum[MaxN], ans[MaxN];
struct Node{
	int serial, value;
};
stack<Node> s;

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
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		sum[i] = sum[i-1] = a[i];
	}
	for(int i=1; i<=n; i++){
		while(!s.empty() && s.top().value >= a[i])
			s.pop();
		if(!s.empty()) l[i] = s.top().serial + 1;
		else l[i] = 1;
		s.push((Node){i,a[i]});
	}
	while(!s.empty())
		s.pop();
	for(int i=n; i>=1; i--){
		while(!s.empty() && s.top().value >= a[i])
			s.pop();
		if(!s.empty()) r[i] = s.top().serial - 1;
		else r[i] = n;
		s.push((Node){i,a[i]});
	}
	for(int i=1; i<=n; i++)
		ans[r[i]-l[i]+1] = max(ans[r[i]-l[i]+1], a[i]);
	for(int i=n; i>=1; i--)
		ans[i] = max(ans[i], ans[i+1]);
	for(int i=1; i<=n; i++)
		printf("%lld ", ans[i]);
	return 0;
}