#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
char a[30], b[30], c[30];
int n, t[300], used[30], p[30], u[30], y;

inline bool Check(){
	for(int i=n; i>=1; i--){
		if(t[a[i]] == -1 || t[b[i]] == -1 || t[c[i]] == -1) continue;
		if((t[a[i]] + t[b[i]]) % n != t[c[i]]){
			if((t[a[i]] + t[b[i]] + 1) % n != t[c[i]]) return 0;
		}
	}
	return 1;
}

inline void Try(){
	int jw = 0;
	for(int i=n; i>=1; i--){
		int s = t[a[i]] + t[b[i]] + jw;
		if(t[c[i]] != s%n) return;
		jw = s/n;
	}
	cout << t['A'];
	for(int i='A'+1; i<='A'+n-1; i++)
		cout<<' '<<t[i];
	exit(0);
}

inline void DFS(int now){
	if(now > n){
		Try();
		return ;
	}
	for(int i=n-1; i>=0; i--){
		if(used[i]) continue;
		t[p[now]+'A'-1] = i;
		if(Check()){
			used[i] = 1;
			DFS(now+1);
			used[i] = 0;
		}
	}
	t[p[now]+'A'-1] = -1;
}

signed main(){
	memset(t, -1, sizeof(t));
	scanf("%lld",&n);
	scanf("%s%s%s",a+1,b+1,c+1);
	for(int i=n;i>=1;i--){
		if(!u[a[i]-'A'+1]) p[++y] = a[i]-'A'+1, u[a[i]-'A'+1] = 1;
		if(!u[b[i]-'A'+1]) p[++y] = b[i]-'A'+1, u[b[i]-'A'+1] = 1;
		if(!u[c[i]-'A'+1]) p[++y] = c[i]-'A'+1, u[c[i]-'A'+1] = 1;
	}
	DFS(1);
	return 0;
}