#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003;
char mp[MaxN][MaxN];
int n, m, ans, a[MaxN][MaxN], up[MaxN][MaxN];
int stack[MaxN], value[MaxN], top;

inline bool Judge(char from, char to){
	if(from == 'w') return to == 'a' || to == 'b';
	else if(from == 'x') return to == 'b' || to == 'c';
	else if(from == 'y') return to == 'a' || to == 'c';
	else if(from == 'z') return true;
	else return from == to;
}

inline void Transfer(char to){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++){
			a[i][j] = Judge(mp[i][j],to);
			up[i][j] = a[i][j]? up[i-1][j]+1:0;
		}
}

inline void Reset(){ // Haruki, reset!
	memset(a, 0, sizeof(a));
	memset(up, 0, sizeof(up));
	top = 0;
}

inline void Calculate(char to){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int sum = 0;
			while(top && stack[top] >= up[i][j]){
				sum += value[top];
				ans = max(ans, stack[top]*sum);
				top--;
			}
			sum++;
			stack[++top] = up[i][j];
			value[top] = sum;
		}
		int sum = 0;
		while(top){
			sum += value[top];
			ans = max(ans, stack[top]*sum);
			top--;
		}
	}
}

signed main(){
	while(scanf("%lld%lld", &n, &m) != EOF){
		ans = 0;
		for(int i=1; i<=n; i++)
			scanf("%s", mp[i]+1);
		Reset();
		Transfer('a');
		Calculate('a');
		Reset();
		Transfer('b');
		Calculate('b');
		Reset();
		Transfer('c');
		Calculate('c');
		printf("%lld\n", ans);
	}
	return 0;
}