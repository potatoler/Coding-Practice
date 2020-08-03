#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a, b, num[15], f[15][15][2][2];

inline int DFS(int x, int last, bool limited, bool zero){
	if(!x) return 1;
	if(~f[x][last][limited][zero]) return f[x][last][limited][zero];
	int ans = 0;
	for(int i=0;i<=9;i++)
		if((i<=num[x] || !limited) && (abs(i-last)>=2 || zero)) ans += DFS(x-1, i, limited&&(i==num[x]), zero&&(!i));
	f[x][last][limited][zero] = ans;
	return ans;
}

inline int Calculate(int x){
	int tmp = x, len = 0;
	memset(num, 0, sizeof(num));
	while(tmp){
		num[++len] = tmp % 10;
		tmp /= 10;
	}
	memset(f, -1, sizeof(f));
	return DFS(len, 11, 1, 1);
}

int main(){
	scanf("%d%d",&a,&b);
	printf("%d\n", Calculate(b) - Calculate(a-1));
}