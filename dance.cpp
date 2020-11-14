#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#define int long long
using namespace std;
typedef pair<int,int> mono;
const int MaxN = 15, MaxT = 200005;
int n, logn;
int cnt = 1, a[MaxN], ans[MaxT*MaxN];

class Tri_Tree{
	public:
	struct Node{
		int value;
		bool flag;
		vector<mono> son;
	}node[MaxT*MaxN];
	inline void Update(int x){
		if(!node[x].flag || node[x].son.empty()) return;
		node[x].flag = 0;
		int pos1, pos2;
		for(int i=0; i<3; i++){
			if(node[x].son[i].first == 1) pos1 = i;
			if(node[x].son[i].first == 2) pos2 = i;
		}
		swap(node[x].son[pos1].first, node[x].son[pos2].first);
	}
	
	inline void Reverse(int idx){
		node[idx].flag ^= 1;
		return;
	}
	
	inline void Build(int x, int dep, int val){
		if(dep == logn+1){
			node[x].value = val;
			return;
		}
		node[x].son.push_back(make_pair(0,++cnt));
		Build(cnt, dep+1, val);
		node[x].son.push_back(make_pair(1, ++cnt));
		Build(cnt, dep+1, val+a[dep-1]);
		node[x].son.push_back(make_pair(2, ++cnt));
		Build(cnt, dep+1, val+a[dep-1]*2);
	}
	
	inline void Change(int x){
		if(node[x].son.empty()) return;
		if(node[x].flag){
			Update(x);
			for(int i=0; i<3; i++)
				Reverse(node[x].son[i].second);
		}
		for(int i=0; i<3; i++){
			node[x].son[i].first++;
			node[x].son[i].first %= 3;
			if(!node[x].son[i].first) Change(node[x].son[i].second);
		}
	}
	
	inline void Reset(int x, int pos, int dep){
		if(node[x].son.empty()) ans[node[x].value] = pos;
		else{
			if(node[x].flag){
				Update(x);
				for(int i=0; i<3; i++) Reverse(node[x].son[i].second);
			}
			for(int i=0; i<3; i++) Reset(node[x].son[i].second, pos + a[dep-1] * node[x].son[i].first, dep+1);
		}
	}
}tree;

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
	int tmp = 1;
	for(int i=1; i<=n; i++)
		tmp *= 3;
	a[0] = 1;
	for(int i=1; i<=n; i++)
		a[i] = a[i-1] * 3;
	logn = n;
	n = tmp;
	tree.Build(1, 1, 0);
	string str = "";
	cin >> str;
	for(int i=0; i<str.length(); i++){
		bool type = (str[i] == 'S');
		if(type) tree.node[1].flag ^= 1;
		else tree.Change(1);
	}
	tree.Reset(1, 0, 1);
	for(int i=0; i<n; i++)
		printf("%lld ", ans[i]);
	return 0;
}