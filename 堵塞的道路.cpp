#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
struct SegmentTree{
	int lseg, rseg;
	bool l, r, u, d, p, q;
}seg[MaxN*4];
bool connected[MaxN][2];
int n;
char op[10];

inline void PassTag(SegmentTree &x, SegmentTree l, SegmentTree r){
	x.lseg = l.lseg;
	x.rseg = r.rseg;
	x.l = l.l | (l.u & connected[l.rseg][0] & r.l & connected[l.rseg][1] & l.d);
	x.r = r.r | (r.u & connected[l.rseg][0] & l.r & connected[l.rseg][1] & r.d);
	x.u = (l.u & connected[l.rseg][0] & r.u) | (l.p & connected[l.rseg][1] & r.q);
	x.d = (l.d & connected[l.rseg][1] & r.d) | (l.q & connected[l.rseg][0] & r.p);
	x.p = (l.u & connected[l.rseg][0] & r.p) | (l.p & connected[l.rseg][1] & r.d);
	x.q = (l.d & connected[l.rseg][1] & r.q) | (l.q & connected[l.rseg][0] & r.u);
}

inline void Build(int x, int l, int r){
	if(l == r){
		seg[x].lseg = l; seg[x].rseg = r;
		seg[x].u = seg[x].d = true;
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid); Build(x*2+1, mid+1, r);
	PassTag(seg[x], seg[x*2], seg[x*2+1]);
}

inline void InlineChange(int x, int p, int row, bool val){
	int mid = (seg[x].lseg + seg[x].rseg) / 2;
	if(mid == p){
		connected[mid][row] = val;
		PassTag(seg[x], seg[x*2], seg[x*2+1]);
		return;
	}
	if(mid >= p) InlineChange(x*2, p, row, val);
	else InlineChange(x*2+1, p, row, val);
	PassTag(seg[x], seg[x*2], seg[x*2+1]);
}

inline void CrosslineChange(int x, int p, int val){
	if(seg[x].lseg == seg[x].rseg){
		seg[x].l = seg[x].r = seg[x].p = seg[x].q = val;
		return;
	}
	int mid = (seg[x].lseg + seg[x].rseg) / 2;
	if(mid >= p) CrosslineChange(x*2, p, val);
	else CrosslineChange(x*2+1, p, val);
	PassTag(seg[x], seg[x*2], seg[x*2+1]);
}

inline SegmentTree Ask(int x, int ql, int qr){
	if(seg[x].lseg >= ql && seg[x].rseg <= qr) return seg[x];
	int mid = (seg[x].lseg + seg[x].rseg) / 2;
	if(mid >= qr) return Ask(x*2, ql, qr);
	else if(mid < ql) return Ask(x*2+1, ql, qr);
	else{
		SegmentTree ans;
		PassTag(ans, Ask(x*2, ql, qr), Ask(x*2+1, ql, qr));
		return ans;
	}
}

int main(){
	scanf("%d",&n);
	Build(1,1,n);
	while(scanf("%s",op) && op[0] != 'E'){
		int r1, c1, r2, c2;
		scanf("%d%d%d%d",&r1, &c1, &r2, &c2);
		if(op[0] == 'C'){
			if(r1 == r2) InlineChange(1, min(c1,c2), r1-1, false);
			else CrosslineChange(1, c1, false);
		}
		else if(op[0] == 'O'){
			if(r1 == r2) InlineChange(1, min(c1,c2), r1-1, true);
			else CrosslineChange(1, c1, true);
		}
		else if(op[0] == 'A'){
			if(c1 > c2){
				swap(c1, c2);
				swap(r1, r2);
			}
			SegmentTree ans1 = Ask(1, c1, c2), ans2 = Ask(1, 1, c1), ans3 = Ask(1, c2, n);
			bool fl = false;
			if(r1 == 1){
				if(r2 == 1){
					if(ans1.u) fl = true;
					if(ans2.r && ans1.d && ans3.l) fl = true;
				}
				else{
					if(ans1.p) fl = true;
					if(ans2.r && ans1.d) fl = true;
					if(ans3.l && ans1.u) fl = true;
				}
			}
			else{
				if(r2 == 1){
					if(ans1.q) fl = true;
					if(ans2.r && ans1.u) fl = true;
					if(ans3.l && ans1.d) fl = true;
				}
				else{
					if(ans1.d) fl = true;
					if(ans2.r && ans1.u && ans3.l) fl = true;
				}
			}
			if(fl) printf("Y\n");
			else printf("N\n");
		}	
	}
	return 0;
}