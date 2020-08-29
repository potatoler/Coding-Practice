#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int Mod = 1000000007;
bool unsolvable = true;
int n, m, ans, cntSolution, sum, a[102], solution[1000006];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = (num * 10 + ch - '0') % Mod;
		ch = getchar();
	}
	return num * op;
}

inline void Write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9) Write(x/10);
	putchar(x%10 + '0');
	return;
}

inline bool Qin_Algorithm(int x){
	sum = 0;
	for(int i=n; i>=1; i--)
		sum = ((a[i] + sum) * x) % Mod;
	sum = (sum + a[0]) % Mod;
	return !sum;
}

signed main(){
	n = Read(), m = Read();
	for(int i=0; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=m; i++){
		if(Qin_Algorithm(i)){
			unsolvable = false;
			ans++;
			solution[++cntSolution] = i;
		}
	}
	if(unsolvable){
		Write(ans);
		return 0;
	}
	Write(ans), printf("\n");
	for(int i=1; i<=cntSolution; i++)
		Write(solution[i]), printf("\n");
	return 0;
}