#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 500004;
priority_queue<int> q;
int n, k, m, ans, value[MaxN];
bool expensive[MaxN];
struct Item{
	int serial, price;
}ori[MaxN], sale[MaxN];
inline bool Decrease(Item a, Item b){ return a.price < b.price; }
inline bool Increase(Item a, Item b){ return a.price > b.price; }

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
	// freopen("shopping.in", "r", stdin);
	// freopen("shopping.out", "w", stdout);
	n = Read(), k = Read(), m = Read();
	for(int i=1; i<=n; i++){
		ori[i].price = Read(), sale[i].price = Read();
		ori[i].serial = sale[i].serial = i;
		value[i] = ori[i].price;
		expensive[i] = true;
	}
	sort(ori+1, ori+1+n, Decrease);
	sort(sale+1, sale+1+n, Decrease);
	int l = 1, r = 1;
	for(int i=1; i<=k; i++){
		if(sale[i].price <= m){
			m -= sale[i].price;
			ans++;
			l = i+1;
			q.push(-value[sale[i].serial] + sale[i].price);
			expensive[sale[i].serial] = false;
		}
	}
	if(l != 1){
		for(int i=1; i<=n; i++){
			while(expensive[ori[r].serial] == false && r <= n)
				r++;
			if((m < ori[r].price && m < -q.top() + sale[l].price) || ans == n) break;
			if(ori[r].price < -q.top() + sale[l].price){
				expensive[ori[r].price] = false;
				m -= ori[r].price;
				r++;
			}
			else{
				expensive[ori[l].price] = false;
				m += q.top() - sale[l].price;
				q.pop();
				l++;
				q.push(-value[sale[l].serial] + sale[l].price);
			}
			ans++;
		}
	}
	printf("%lld", ans);
	return 0;
}