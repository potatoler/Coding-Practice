#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, k, a[MaxN], f[MaxN][MaxN], cost[MaxN][MaxN];
class TopQueue{
	public:
		priority_queue<int> left;
		priority_queue<int, vector<int>, greater<int> > right;
		int sumLeft, sumRight;

		inline void Clear(){
			priority_queue<int> newBig;
			priority_queue<int, vector<int>, greater<int> > newSmall;
			left.swap(newBig);
			right.swap(newSmall);
			sumLeft = sumRight = 0;
		}

		inline void Push(int w){
			if(left.empty()) left.push(w), sumLeft += w;
			else if(w>left.top()) right.push(w), sumRight += w;
			else left.push(w), sumLeft += w;
			while(left.size() > right.size()+1){
				sumRight += left.top();
				sumLeft -= left.top();
				right.push(left.top());
				left.pop();
			}
			while(left.size() < right.size()){
				sumLeft += right.top();
				sumRight -= right.top();
				left.push(right.top());
				right.pop();
			}
		}
}tq;

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

inline void Reset(){ // Haruki, reset!
	for(int i=0; i<MaxN; i++)
		for(int j=0; j<MaxN; j++)
			f[i][j] = INT_MAX;
		f[0][0] = 0;
}

signed main(){
	while(true){
		n = Read(), k = Read();
		if(!n && !k) break;
		for(int i=1; i<=n; i++)
			a[i] = Read();
		for(int i=1; i<=n; i++){
			tq.Clear();
			for(int j=i; j<=n; j++){
				tq.Push(a[j]);
				int tmp = tq.left.top();
				cost[i][j] = tmp * tq.left.size() - tq.sumLeft;
				if(!tq.right.empty()) cost[i][j] += tq.sumRight - tmp * tq.right.size();
			}
		}
		Reset();
		for(int i=1; i<=k; i++)
			for(int j=1; j<=n; j++)
				for(int l=0; l<j; l++)
					f[i][j] = min(f[i][j], f[i-1][l]+cost[l+1][j]);
		printf("%lld\n", f[k][n]);
	}
	return 0;
}