#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m, ID[MaxN], f[MaxN];
typedef pair<int,int> period;
vector<period> gate[MaxN], cur;
struct Node{
	int periodID, gateID, t;
	bool operator > (const Node &y) const {
		return t > y.t;
	}
};
priority_queue<Node, vector<Node>, greater<Node> > q;

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

inline void Calculate(Node node, int x){
	int r = gate[node.gateID][node.periodID - ID[node.gateID]].second;
//	printf("%lld\n", r);
	int i = lower_bound(gate[x].begin(), gate[x].end(), period(node.t+1,0)) - gate[x].begin() - 1;
	if(gate[x][i].second >= node.t + 1){
		if(f[ID[x]+i] > node.t + 1){
			f[ID[x]+i] = node.t + 1;
			q.push((Node){ID[x]+i, x, node.t+1});
		}
	}
	i++;
	while(i < gate[x].size() && gate[x][i].first <= r+1){
//		printf("%lld\n", gate[x][i].first);
		if(f[ID[x]+i] > gate[x][i].first){
			f[ID[x]+i] = gate[x][i].first;
			q.push((Node){ID[x]+i, x, gate[x][i].first});
		}
		i++;
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int a = Read(), b = Read(), c = Read();
		gate[a].push_back(period(b,c));
	}
	gate[0].push_back(period(0,0x3f3f3f3f));
	gate[n+1].push_back(period(0,0x3f3f3f3f));
	ID[1] = 1;
	for(int i=1; i<=n; i++){
		sort(gate[i].begin(), gate[i].end());
//		for(auto p : gate[i]){
//			printf("%lld %lld\n", p.first, p.second);
//		}
		cur.clear();
		int r = -1;
		for(auto p : gate[i]){
			if(p.first > r+1) cur.push_back(period(r+1, p.first-1));
			r = max(r, p.second);
		}
//		printf("%d\n", r);
		cur.push_back(period(r+1, 0x3f3f3f3f));
		gate[i] = cur;
		ID[i+1] = ID[i] + gate[i].size();
	}
//	for(int i=1; i<=n+1; i++)
//		printf("%lld ", ID[i]);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	q.push((Node){0,0,0});
	while(q.size()){
		Node x = q.top();
		q.pop();
		if(x.t > f[x.periodID]) continue;
		if(x.gateID > 0) Calculate(x, x.gateID-1);
		if(x.gateID < n+1) Calculate(x, x.gateID+1);
	}
	printf("%lld", f[ID[n+1]]);
	return 0;
}