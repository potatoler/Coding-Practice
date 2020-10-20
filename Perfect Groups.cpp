#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#define int long long
using namespace std;
const int MaxN = 5003;
int n, a[MaxN], idx[MaxN], ans[MaxN], cntNum;
bool visited[MaxN];
map<int,int> mp;

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

inline int Transform(int x){
	int op = 1;
	if(x < 0){
		op = -1;
		x = -x;
	}
	for(int i=2; i*i<=x; i++)
		while(x % (i*i) == 0)
			x /= (i*i);
	return x * op;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		a[i] = Transform(a[i]);
		if(!mp[a[i]]){
			mp[a[i]] = ++cntNum;
			idx[i] = cntNum;
		}
		else idx[i] = mp[a[i]];
	}
	for(int i=1; i<=n; i++){
		int cnt = 0;
		memset(visited, false, sizeof(visited));
		for(int j=i; j<=n; j++){
			if(!a[j]){
				if(!cnt) ans[1]++;
				else ans[cnt]++;
			}
			else{
				if(!visited[idx[j]]){
					visited[idx[j]] = true;
					cnt++;
				}
				ans[cnt]++;
			}
		}
	}
	for(int i=1; i<=n; i++)
		printf("%lld ", ans[i]);
	return 0;
}