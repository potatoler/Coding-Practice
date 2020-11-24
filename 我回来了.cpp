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
const int MaxN = 100005;
int n, m, a[MaxN];
bool visited[MaxN], have[MaxN];
int stack[MaxN], top;

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

class BinaryIndexedTree{
	private:
	int storage[MaxN];
	public:
	inline void Add(int pos, int val){
		while(pos<=n){
			storage[pos] += val;
			pos += lowbit(pos);
		}
		return;
	}
	
	inline int Ask(int pos){
		int res = 0;
		while(pos){
			res += storage[pos];
			pos -= lowbit(pos);
		}
		return res;
	}
}exist, will;

class SegmentTree{
	private:
	vector<int> storage[MaxN*4];
	public:
	inline void Insert(int x, int l, int r, int ql, int qr, int w){
		if(ql<=l && r<=qr){
			storage[x].push_back(w);
			return;
		}
		int mid = (l+r) >> 1;
		if(ql <= mid) Insert(x<<1, l, mid, ql, qr, w);
		if(qr > mid) Insert(x<<1|1, mid+1, r, ql, qr, w);
		return;
	}
	
	inline void Query(int x, int l, int r, int w){
		for(auto i:storage[x]){
			if(!visited[i]){
				visited[i] = true;
				stack[++top] = i;
			}
		}
		storage[x].clear();
		if(l<r){
			int mid = (l+r) >> 1;
			if(w <= mid) Query(x<<1, l, mid, w);
			else Query(x<<1|1, mid+1, r, w);
		}
		return;
	};
}Seg;

inline void Work(int x){
	int l = 0, r = 0;
	do{
		a[x]++;
		will.Add(x,1);
		l = a[x]*x;
		r = min(a[x]*x+x, n) - 1;
	}while(l<=n-1 && exist.Ask(r+1) > exist.Ask(l));
	if(l <= n-1) Seg.Insert(1, 0, n-1, l, r, x);
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		Seg.Insert(1, 0, n-1, 0, i-1, i);
		will.Add(i,1);
	}
	while(m--){
		int op = Read();
		if(op == 1){
			int h = Read()-1;
			if(!have[h]){
				have[h] = 1;
				exist.Add(h+1, 1);
				top = 0;
				Seg.Query(1, 0, n-1, h);
				for(int i=1; i<=top; i++){
					int x = stack[i];
					if(a[x] == h/x) Work(x);
					visited[x] = false;
				}
			}
		}
		else{
			int l = Read(), r = Read();
			int ans = will.Ask(r) - will.Ask(l-1);
			printf("%lld\n", ans);
		}
	}
	return 0;
}