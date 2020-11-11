#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;

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

inline int ExGCD(int a, int b, int &x, int &y){
	int k = a;
	if(!b){
		x = 1;
		y = 0;
		return k;
	}
	k = ExGCD(b, a%b, x, y);
	int z = x;
	x = y;
	y = z - a/b * y;
	return k;
}

signed main(){
//	freopen("function.in", "r", stdin);
//	freopen("function.out", "w", stdout);
	int T = Read();
	while(T--){
		int a = Read(), b = Read(), c = Read();
		int x = 0, y = 0;
		if(a + b == c){
			printf("1\n");
			continue;
		}
		if(a < 0 && b < 0){
			a = -a;
			b = -b;
			c = -c;
		}
		int k = ExGCD(a, b, x, y);
		if(c % k){
			printf("0\n");
			continue;
		}
		if(!a || !b){
			if(abs(a) > abs(b)) swap(a,b);
			if(!c){
				printf("0\n");
				continue;
			}
			else if((c < 0) ^ (b < 0)){
				printf("0\n");
				continue;
			}
			else{
				printf("ZenMeZheMeDuo\n");
				continue;
			}
		}
		else if((a < 0) ^ (b < 0)){
			printf("ZenMeZheMeDuo\n");
			continue;
		}
		else if(a == 0 && b == 0){
			if(!c){
				printf("ZenMeZheMeDuo\n");
				continue;
			}
			else{
				printf("0\n");
				continue;
			}
		}
		a /= k, b /= k, c /= k;
		ExGCD(a, b, x, y);
		x *= c, y *= c;
		if(x <= 0){
			int t = -x / b + 1;
			x = x % b + b;
			y = y - t * a;
			if(y <= 0){
				printf("0\n");
				continue;
			}
		}
		if(y <= 0){
			int t = -y / a + 1;
			y = y % a + a;
			x = x - t * b;
			if(x <= 0){
				printf("0\n");
				continue;
			}
		}
		int t = x / b;
		x %= b;
		if(x == 0) x += b, t--;
		y += t * a;
		int minx = x;
		t = y / a;
		y %= a;
		if(!y) y += a, t--;
		x += t * b;
		int cnt = (x - minx) / b + 1;
		if(cnt > 65535) printf("ZenMeZheMeDuo\n");
		else printf("%lld\n", cnt);
	}
	return 0;
}