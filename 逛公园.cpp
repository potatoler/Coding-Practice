#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long
using namespace std;
int t,d[100001],f[100001][51],n,m,k,p;
bool working[100001][51];
struct node  {
    int to,len;
};
vector<node> head[100001];
vector<node> h[100001];

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

inline int dp(int root, int l){
    int ans=0;			
    if (l<0||l> k) return 0;
    if (working[root][l]){
        working[root][l]=false;
        return -1;
    }
    if(f[root][l]!=-1)   
   		return f[root][l];
    working[root][l]=true;
    for (int i=0;i<h[root].size();i++){
        node e= h[root][i];
        int val=dp(e.to,d[root]+l-d[e.to]-e.len);
        if (val==-1) {
            working[root][l]=false;
            return -1;
        }
        ans=(ans+val)%p;
    }
    working[root][l] = false;	
    if (root==1&&l==0) ans++;
    f[root][l]=ans;
    return ans;
}

int work(){
    n = Read(), m = Read(), k = Read(), p = Read();
    for (int i=1;i<=n;i++){
        head[i].clear();
        h[i].clear();
    }
    for (int i=1;i<= m;i++){
        int a = Read(), b = Read(), c = Read();
        node  e;
        e.to=b;	e.len=c;
        head[a].push_back(e);
        e.to=a;
        h[b].push_back(e);
    }
    memset(d,0x3f,sizeof(d));
    memset(f,-1,sizeof(f));
    queue<int>q;
    q.push(1);	d[1]=0;
    while (!q.empty()){
        int x=q.front();
        q.pop();
        for (int i=0;i<head[x].size();i++){
            if (d[head[x][i].to]>d[x]+head[x][i].len){
                d[head[x][i].to]=d[x]+head[x][i].len;
                q.push(head[x][i].to);
            }
        }
    }
    int ans=0;
    for (int i=0;i<=k;i++){
        int val=dp(n,i);
        if (val==-1)   return -1;
        ans=(ans+val)%p;
    }
    return ans;
}

signed main(){
    t = Read();
    while(t--) printf("%lld\n", work());
    return 0;
}