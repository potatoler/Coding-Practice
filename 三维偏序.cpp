#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 200005;
struct Node{
	int a, b, c, cnt, ans;
}ori[MaxN], pro[MaxN];
int n, m, k, tree[MaxN], top, sum[MaxN], mx;

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

inline bool cmpa(Node x, Node y){
	if(x.a == y.a){
		if(x.b == y.b) return x.c < y.c;
		else return x.b < y.b;
	}
	else return x.a < y.a;
}

inline bool cmpb(Node x, Node y){
	if(x.b == y.b) return x.c < y.c;
	else return x.b < y.b;
}

inline int Lowbit(int x){
	return x & (-x);
}

inline void Add(int x, int y){
	while(x <= mx){
		tree[x] += y;
		x += Lowbit(x);
	}
	return;
}

inline int Sum(int x){
	int sum = 0;
	while(x){
		sum += tree[x];
		x -= Lowbit(x);
	}
	return sum;
}

inline void CDQ(int l, int r){
	if(l == r) return;
	int mid = (l + r) / 2;
	CDQ(l, mid), CDQ(mid+1, r);
	sort(pro+l, pro+mid+1, cmpb), sort(pro+mid+1, pro+r+1, cmpb);
	int p, q=l;
	for(int p=mid+1; p<=r; p++){
		while(pro[p].b >= pro[q].b && q <= mid){
			Add(pro[q].c, pro[q].cnt);
			q++;
		}
		pro[p].ans += Sum(pro[p].c);
	}
	for(p=l; p<q; p++)
		Add(pro[p].c, -pro[p].cnt);
}

signed main(){
	n = Read(), k = Read();
	mx = k;
	for(int i=1; i<=n; i++)
		ori[i].a = Read(), ori[i].b = Read(), ori[i].c = Read();
	sort(ori+1, ori+1+n, cmpa);
//	for(int i=1;i<=n;i++)
//			printf("%lld %lld %lld\n", ori[i].a, ori[i].b, ori[i].c);
	for(int i=1; i<=n; i++){
		top++;
		if(ori[i].a!=ori[i+1].a || ori[i].b!=ori[i+1].b || ori[i].c!=ori[i+1].c){
			m++;
			pro[m].a = ori[i].a;
			pro[m].b = ori[i].b;
			pro[m].c = ori[i].c;
			pro[m].cnt = top;
			top = 0;
//			printf("%lld ", pro[m].cnt);
		}
	}
	CDQ(1, m);
//	for(int i=1;i<=m;i++)
//		printf("%lld %lld %lld %lld %lld\n", pro[i].a, pro[i].b, pro[i].c, pro[i].cnt, pro[i].ans);
	for(int i=1; i<=m; i++)
		sum[pro[i].ans + pro[i].cnt-1] += pro[i].cnt;
	for(int i=0; i<n; i++)
		printf("%lld\n", sum[i]);
	return 0;
}