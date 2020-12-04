#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int MaxN = 1000006;
int n, a[MaxN], ans[MaxN];
class BinaryIndexedTree{
private:
	int storage[MaxN];
public:
	inline void Add(int pos, int w){
		while(pos <= n){
			storage[pos] += w;
			pos += lowbit(pos);
		}
		return;
	}
	inline int Query(int pos){
		int res = 0;
		while(pos > 0){
			res += storage[pos];
			pos -= lowbit(pos);
		}
		return res;
	}
}BIT;

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
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		BIT.Add(i,i);
	}
	for(int i=n; i>=1; i--){
		int l = 1, r = n, res = n;
		while(l<=r){
			int mid = (l+r) >> 1;
			if(BIT.Query(mid-1) <= a[i]){
				res = mid;
				l = mid+1;
			}
			else r = mid-1;
		}
		ans[i] = res;
		BIT.Add(res, -res);
	}
	for(int i=1; i<n; i++)
		printf("%lld ", ans[i]);
	printf("%lld", ans[n]);
}