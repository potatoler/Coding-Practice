#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000000009;
int s;
struct Point{
	int x, y;
}vertex[4];

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

inline int GCD(int a, int b){
	return b==0? a : GCD(b, a%b);
}

inline int OnEdge(){
	int res = 0;
	for(int i=0; i<3; i++)
		res += GCD(abs(vertex[i].x - vertex[(i+1)%3].x), abs(vertex[i].y - vertex[(i+1)%3].y));
	return res;
}

inline int Product(Point a1, Point b1, Point a2, Point b2){
	int x_1 = b1.x - a1.x, y_1 = b1.y - a1.y, x_2 = b2.x - a2.x, y_2 = b2.y - a2.y;
	return abs(x_1 * y_2 - x_2 * y_1);
}

inline int Inside(){
	return (abs(s) - OnEdge()) / 2 + 1;
}

signed main(){
	int T = Read();
	while(T--){
		vertex[0] = (Point){Read(), Read()};
		vertex[1] = (Point){Read(), Read()};
		vertex[2] = (Point){Read(), Read()};
		s = Product(vertex[0], vertex[1], vertex[0], vertex[2]);
//		printf("%lld ", OnEdge());
		if(!s){
			printf("0");
			continue;
		}
		printf("%lld\n", OnEdge() + Inside());
	}
	return 0;
}