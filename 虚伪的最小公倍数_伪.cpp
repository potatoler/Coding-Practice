#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int Mod = 998244353;
int T, n, k;

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

inline int GCD(int x, int y){
	if(!y) return x;
	return GCD(y, x%y);
}

signed main(){
	T = Read();
	while(T--){
		n = Read(), k = Read();
		int ans = 1, gcd = 1, mul = 1;
		for(int i_1=1; i_1<=n; i_1++){
			for(int i_2=1; i_2<=n; i_2++){
				if(k == 2){
					mul = i_1 * i_2;
					gcd = GCD(i_1, i_2);
					ans = ans * (mul/gcd) % Mod;
					continue;
				}
				for(int i_3=1; i_3<=n; i_3++){
					if(k == 3){
						mul = i_1 * i_2 * i_3;
						gcd = GCD(GCD(i_1, i_2), i_3);
						ans = ans * (mul/gcd) % Mod;
						continue;
					}
					for(int i_4=1; i_4<=n; i_4++){
						if(k == 4){
							mul = i_1 * i_2 * i_3 * i_4;
							gcd = GCD(GCD(i_1, i_2), GCD(i_3, i_4));
							ans = ans * (mul/gcd) % Mod;
							continue;
						}
						for(int i_5=1; i_5<=n; i_5++){
							mul = i_1 * i_2 * i_3 * i_4 * i_5;
							gcd = GCD(GCD(GCD(i_1, i_2), GCD(i_3, i_4)), i_5);
							ans = ans * (mul/gcd) % Mod;
						}
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}