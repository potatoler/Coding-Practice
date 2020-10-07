#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005, MaxB = 320;
int n, c, m, a[MaxN], f[MaxB][MaxB], cnt[MaxB][MaxN], side[MaxB], block[MaxN], lastans, len, num[MaxN], stack[MaxN], top;

inline int Read(){
	int number = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		number = number * 10 + ch - '0';
		ch = getchar();
	}
	return number * op;
}

inline void Block(){
	for(int i=1; i<=n; i++){
		a[i] = Read();
		block[i] = (i-1) / len + 1;
		if(block[i] != block[i-1]) side[block[i]] = i;
	}
	block[n+1] = block[n] + 1;
	side[block[n+1]] = n + 1;
}

inline void Init(){
	for(int i=1; i<=block[n]; i++){
		int tmp = 0;
		for(int j=side[i]; j<=n; j++){
			cnt[i][a[j]]++;
			if((cnt[i][a[j]] & 1) && (cnt[i][a[j]] > 1)) tmp--;
			else if((cnt[i][a[j]] & 1) == 0) tmp++;
			if(block[j] != block[j+1]) f[i][block[j]] = tmp;
		}
	}
	return;
}

inline int Query(int l, int r){
	int ans = 0;
	if(block[l] == block[r]){
		for(int i=l; i<=r; i++){
			num[a[i]]++;
			stack[++top] = a[i];
		}
		while(top){
			int cur = stack[top--];
			if(num[cur] != 0){
				ans += (num[cur] & 1) ^ 1;
				num[cur] = 0;
			}
		}
		return lastans = ans;
	}
	if(block[l] + 1 <= block[r] - 1) ans += f[block[l]+1][block[r]-1];
	for(int i=l; i<side[block[l]+1]; i++){
		num[a[i]]++;
		stack[++top] = a[i];
	}
	for(int i=side[block[r]]; i<=r; i++){
		num[a[i]]++;
		stack[++top] = a[i];
	}
	while(top){
		int cur = stack[top--];
		if(num[cur] != 0){
			if(cnt[block[l]+1][cur] - cnt[block[r]][cur] > 0 && ((cnt[block[l]+1][cur] - cnt[block[r]][cur]) & 1) == 0 && (num[cur] & 1)) ans--;
			else if(cnt[block[l]+1][cur] - cnt[block[r]][cur] > 0 && ((cnt[block[l]+1][cur] - cnt[block[r]][cur]) & 1) && (num[cur] & 1)) ans++;
			else if(cnt[block[l]+1][cur] - cnt[block[r]][cur] == 0 && (num[cur] & 1) == 0) ans++;
			num[cur] = 0;
		}
	}
	return lastans = ans;
}

signed main(){
	n = Read(), c = Read(), m = Read();
	len = sqrt(n);
	Block();
	Init();
	while(m--){
		int l = Read(), r = Read();
		l = (l + lastans) % n + 1;
		r = (r + lastans) % n + 1;
		if(l > r) swap(l, r);
		printf("%lld\n", Query(l, r));
	}
	return 0;
}