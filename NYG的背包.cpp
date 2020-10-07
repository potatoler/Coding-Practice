#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int MaxN = 100005;
int T, v, n, cntMore, cntLess, available;
bool overFill;
struct Item{
	int a, b;
}moreSpace[MaxN], lessSpace[MaxN];
inline bool cmpM(Item x, Item y){
	return x.a < y.a;
}
inline bool cmpL(Item x, Item y){
	return x.b > y.b;
}

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
	T = Read();
	while(T--){
		n = Read(), available = v = Read();
		overFill = false;
		cntMore = cntLess = 0;
		for(int i=1; i<=n; i++){
			int aa = Read(), bb = Read();
			if(bb > aa) moreSpace[++cntMore] = (Item){aa,bb};
			else lessSpace[++cntLess] = (Item){aa,bb};
		}
//		exit(0);
		sort(moreSpace+1, moreSpace+1+cntMore, cmpM);
		sort(lessSpace+1, lessSpace+1+cntLess, cmpL);
		for(int i=1; i<=cntMore; i++){
			available -= moreSpace[i].a;
			if(available < 0){
				overFill = true;
				break;
			}
			available += moreSpace[i].b;
		}
		if(!overFill){
			for(int i=1; i<=cntLess; i++){
				available -= lessSpace[i].a;
				if(available < 0){
					overFill = true;
					break;
				}
				available += lessSpace[i].b;
			}
		}
		if(overFill) puts("No");
		else puts("Yes");
	}
	return 0;
}