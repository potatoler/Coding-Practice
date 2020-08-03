#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
#define thisKey ky[nodeSerial[headNode[x]]]
using namespace std;
const int MaxN = 120000, Inf = INT_MAX;
int n, m, elemCount;
int missKey, goodTap, perfectClick, maxCombo, curCombo;
struct Key{int t, a, b, judgeTime, ifJudged;} ky[MaxN];
struct Click{int t, pos;} click[MaxN];
int nodeCount, headNode[MaxN << 4], lastNode[MaxN << 4], nextNode[MaxN << 10], nodeSerial[MaxN << 10];
bool cmpKey(Key x, Key y){return x.t < y.t;}
bool cmpClick(Click x, Click y){return x.t < y.t;}
bool cmpJudge(Key x, Key y){return x.judgeTime < y.judgeTime || (x.judgeTime == y.judgeTime && x.ifJudged < y.ifJudged);}
int posData[MaxN << 3];
inline int getPos(int x){return lower_bound(posData+1, posData+elemCount+1, x) - posData;}
inline void AddNode(int x,  int ser){
	//the x-th position on the segment tree with ser-th key
	//it's worth noticed that for position x there may be more than one key with different serial
	nodeCount++;
	if(!headNode[x]) headNode[x] = lastNode[x] = nodeCount;
	else nextNode[lastNode[x]] = nodeCount, lastNode[x] = nodeCount;
	nodeSerial[nodeCount] = ser;
}
inline void Build(int l, int r, int reqL, int reqR, int x, int ser){
	//in the traditional segment tree we can simply give a[i]'s value to the tree but here we need to used the AddNote function
	if(l >= reqL && r <= reqR){AddNode(x, ser); return;}
	int mid = (l + r) / 2;
	if(reqL <= mid) Build(l, mid, reqL, reqR, x*2, ser);
	if(reqR > mid) Build(mid+1, r, reqL, reqR, x*2+1, ser);
}
//obviously the big number in the functions below comes from the 0.6 and 1 in game rule: after dispersing these numbers also get bigger
inline void Refresh(int x, int t){
	//keys that have been clicked should be deleted
	while(headNode[x]){
		if(thisKey.t + 60000 <= t){
			if(!thisKey.ifJudged){
				thisKey.judgeTime = thisKey.t + 60000;
				thisKey.ifJudged = 1;
			}
			headNode[x] = nextNode[headNode[x]];
		}
		else if(thisKey.ifJudged) headNode[x] = nextNode[headNode[x]];
		else break;
	}
}
inline int JudgeTimeCal(int x, int t){
	if(thisKey.t - t >= 100000) return Inf;
	else return thisKey.t;
}
inline int GetJudgeTime(int l, int r, int pos, int x, int t){
	//delete judged keys before EVERY SINGLE TIME of JUDGE!
	Refresh(x, t);
	if(l == r) return JudgeTimeCal(x, t);
	int mid = (l + r) / 2;
	if(pos <= mid) return min(JudgeTimeCal(x, t), GetJudgeTime(l, mid, pos, x*2, t));
	else return min(JudgeTimeCal(x, t), GetJudgeTime(mid+1, r, pos, x*2+1, t));
}
inline void Judge(int l, int r, int pos, int x, int t, int jt){
	while(thisKey.t == t){
		if(!thisKey.ifJudged){
			thisKey.judgeTime = jt;
			if(abs(thisKey.t - jt) < 20000) thisKey.ifJudged = 3;
			else if(abs(thisKey.t - jt) < 60000) thisKey.ifJudged = 2;
			else thisKey.ifJudged = 1;
		}
		headNode[x] = nextNode[headNode[x]];
	}
	if(l == r) return;
	int mid = (l + r) / 2;
	if(pos <= mid) Judge(l, mid, pos, x*2, t, jt);
	else Judge(mid+1, r, pos, x*2+1, t, jt);
}
int main(){
	//intput and have keys dispersed
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		double t, a, b;
		scanf("%lf%lf%lf",&t,&a,&b);
		ky[i].t = t*1e5+0.5, ky[i].a = a*1e5+0.5, ky[i].b = b*1e5+0.5;
		posData[++elemCount] = ky[i].a, posData[++elemCount] = ky[i].b;
	}
	for(int i=1;i<=m;i++){
		double t, p;
		scanf("%lf%lf",&t,&p);
		click[i].t = t*1e5+0.5, click[i].pos = p*1e5+0.5;
		posData[++elemCount] = click[i].pos;
	}
	ky[0].t = Inf;
	sort(ky+1, ky+1+n, cmpKey);
	sort(click+1, click+1+m, cmpClick);
	sort(posData+1, posData+1+elemCount);
	elemCount = unique(posData+1, posData+elemCount+1) - posData - 1;
	//add keys to the segment tree
	for(int i=1;i<=n;i++)
		Build(1, elemCount, getPos(ky[i].a), getPos(ky[i].b), 1, i);
	//judge
	for(int i=1;i<=m;i++){
		int clickPos = getPos(click[i].pos);
		int t = GetJudgeTime(1, elemCount, clickPos, 1, click[i].t);
		if(t != Inf) Judge(1, elemCount, clickPos, 1, t, click[i].t);
	}
	for(int i=1;i<=n;i++)
		if(!ky[i].ifJudged){
			ky[i].ifJudged = 1;
			ky[i].judgeTime = ky[i].t + 60000;
		}
	sort(ky+1, ky+1+n, cmpJudge);
	for(int i=1;i<=n;i++){
		if(ky[i].ifJudged == 1) missKey++, maxCombo = max(maxCombo, curCombo), curCombo = 0;
		else if(ky[i].ifJudged == 2) curCombo++, goodTap++;
		else if(ky[i].ifJudged == 3) curCombo++, perfectClick++;
	}
	maxCombo = max(maxCombo, curCombo);
	printf("%d %d %d %d", perfectClick, goodTap, missKey, maxCombo);
	return 0;
}