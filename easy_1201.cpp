#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, a[MaxN], last[MaxN];
struct Number{
	int value, serial;
	bool operator < (const Number &y) const {
		if(value == y.value) return serial < y.serial;
		return value < y.value;
	}
}b[MaxN];

struct Segment{
	int value, len, tag, l, r;
};

class SegmentTree{
private:
	Segment tree[MaxN*4];
public:
	inline void Update(int x){
		tree[x].value = tree[x<<1].value;
//		tree[x].tag = tree[x<<1].tag;
		tree[x].len = tree[x<<1].len;
		if(tree[x<<1|1].value < tree[x].value){
			tree[x].value = tree[x<<1|1].value;
//			tree[x].tag = tree[x<<1|1].tag;
			tree[x].len = tree[x<<1|1].len;
		}
		else if(tree[x<<1|1].value == tree[x].value) tree[x].len += tree[x<<1|1].len;
		return;
	}
	
	inline void PassTag(int x){
		if(!tree[x].tag) return;
		tree[x<<1].value += tree[x].tag;
		tree[x<<1|1].value += tree[x].tag;
		tree[x<<1].tag += tree[x].tag;
		tree[x<<1|1].tag += tree[x].tag;
		tree[x].tag = 0;
		return;
	}
	
	inline void Build(int x, int l, int r){
		tree[x].l = l, tree[x].r = r;
		if(l == r){
			tree[x].value = 0;
			tree[x].len = 1;
			return;
		}
		int mid = (l+r) >> 1;
		Build(x<<1, l, mid);
		Build(x<<1|1, mid+1, r);
		Update(x);
	}
	
	inline void Add(int x, int ql, int qr, int w){
		if(ql == tree[x].l && tree[x].r == qr){
			tree[x].value += w;
			tree[x].tag += w;
			return;
		}
		int mid = (tree[x].l + tree[x].r) >> 1;
		PassTag(x);
		if(qr <= mid) Add(x<<1, ql, qr, w);
		else if(ql > mid) Add(x<<1|1, ql, qr, w);
		else{
			Add(x<<1, ql, mid, w);
			Add(x<<1|1, mid+1, qr, w);
		}
		Update(x);
		return;
	}
	
	inline Segment Query(int x, int ql, int qr){
		if(ql == tree[x].l && tree[x].r == qr) return tree[x];
		int mid = (tree[x].l + tree[x].r) >> 1;
		PassTag(x);
		Segment res;
		if(qr <= mid) res = Query(x<<1, ql, qr);
		else if(ql > mid) res = Query(x<<1|1, ql, qr);
		else{
			res = Query(x<<1, ql, mid);
			Segment tmp = Query(x<<1|1, mid+1, qr);
			if(tmp.value < res.value){
				res.value = tmp.value;
//				res.tag = tmp.tag;
				res.len = tmp.len;
			}
			else if(tmp.value == res.value) res.len += tmp.len;
		}
		Update(x);
		return res;
	}
}seg;

class Stack{
private:
	int top, storage[MaxN];
public:
	inline void Push(int x){
		storage[++top] = x;
		return;
	}
	
	inline void Pop(){
		top--;
		return;
	}
	
	inline int Size(){
		return top;
	}
	
	inline int Find(int pos){
		return storage[pos];
	}
	
	inline int Top(int mina = 0){
		return storage[top-mina];
	}
}maxs, mins;

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
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		b[i] = {a[i], i};
	}
	sort(b+1, b+1+n);
	for(int i=1; i<=n; i++)
		if(i==1 || b[i].value > b[i-1].value) last[b[i].serial] = 0;
	else last[b[i].serial] = b[i-1].serial;
	seg.Build(1, 1, n);
	int ans = 0;
	for(int i=1; i<=n; i++){
		seg.Add(1, i, i, i);
		while(maxs.Size() && a[i] > a[maxs.Top()]){
			seg.Add(1, maxs.Top(1)+1, maxs.Top(), a[i] - a[maxs.Top()]);
			maxs.Pop();
		}
		while(mins.Size() && a[i] < a[mins.Top()]){
			seg.Add(1, mins.Top(1)+1, mins.Top(), a[mins.Top()] - a[i]);
			mins.Pop();
		}
		maxs.Push(i), mins.Push(i);
		if(last[i]) seg.Add(1, 1, last[i], 1);
		Segment tmp = seg.Query(1, 1, i);
		if(tmp.value == i) ans += tmp.len;
	}
	printf("%lld", ans);
	return 0;
}