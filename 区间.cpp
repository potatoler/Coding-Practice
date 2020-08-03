#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, cntVertex, leftSide[MaxN], rightSide[MaxN];
struct Vertex{
	int value, serial;
}vertex[MaxN * 2];
struct Section{
	int length, serial;
}section[MaxN * 2];
struct SegmentTree{
	int addTag, maxValue;
}seg[MaxN * 8];

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

inline bool cmpVertex(Vertex ver1, Vertex ver2){
	return ver1.value < ver2.value;
}

inline bool cmpSection(Section sec1, Section sec2){
	return sec1.length < sec2.length;
}

inline void PassTag(int x){
	if(!seg[x].addTag) return;
	seg[x*2].maxValue += seg[x].addTag;
	seg[x*2+1].maxValue += seg[x].addTag;
	seg[x*2].addTag += seg[x].addTag;
	seg[x*2+1].addTag += seg[x].addTag;
	seg[x].addTag = 0;
	return;
}

inline void Change(int x, int l, int r, int ql, int qr, int w){
	if(ql > r || qr < l) return;
	if(ql <= l && r <= qr){
		seg[x].maxValue += w;
		seg[x].addTag += w;
		return;
	}
	PassTag(x);
	int mid  = (l + r) / 2;
	Change(x*2, l, mid, ql, qr, w);
	Change(x*2+1, mid+1, r, ql, qr, w);
	seg[x].maxValue = max(seg[x*2].maxValue, seg[x*2+1].maxValue);
	return;
}

signed main(){
	n = read(), m = read();
	for(int i=1;i<=n;i++){
		int l, r;
		l = read(), r = read();
		section[i] = (Section){r-l, i};
		vertex[++cntVertex] = (Vertex){l, i};
		vertex[++cntVertex] = (Vertex){r, i};
	}
	sort(vertex+1, vertex+1+cntVertex, cmpVertex);
	int num = 0;
	vertex[0].value = -1;
	for(int i=1;i<=cntVertex;i++){
		if(vertex[i].value !=  vertex[i-1].value) num++;
		int s = vertex[i].serial;
		if(!leftSide[s]) leftSide[s] = num;
		else rightSide[s] = num;
	}
	sort(section+1, section+1+n, cmpSection);
	
//	for(int i=1;i<=cntVertex;i++)
//		printf("%lld %lld\n", vertex[i].value, vertex[i].serial);
//	for(int i=1;i<=n;i++)
//		printf("%lld %lld\n", section[i].length, section[i].serial);
//	for(int i=1;i<=n;i++)
//		printf("%lld %lld\n", leftSide[i], rightSide[i]);
	
	int ans = INT_MAX, l = 0, r = 0;
	while(true){
		while(seg[1].maxValue < m && r <= n){
			r++;
			Change(1, 1, num, leftSide[section[r].serial], rightSide[section[r].serial], 1);
		}
		if(seg[1].maxValue < m) break;
		while(seg[1].maxValue >= m && l <= n){
			l++;
			Change(1, 1, num, leftSide[section[l].serial], rightSide[section[l].serial], -1);
		}
		ans = min(ans, section[r].length - section[l].length);
	}
	if(ans == INT_MAX) printf("-1");
	else printf("%lld", ans);
	return 0;
}