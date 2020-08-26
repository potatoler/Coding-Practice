#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
int n,m;
vector<int>v[10005];
bool cando[10005],er[10005];
queue<int>q;
int st,ed;
int ans[10005];

inline int read(){
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

int main()
{    
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read();
		if(a==b)continue;
		v[b].push_back(a);
	}
	st=read(),ed=read();
	cando[ed]=1;
	q.push(ed);
	while(!q.empty())
	{
		int no=q.front();
		q.pop();
		for(int i=0,j=v[no].size();i<j;i++)
			if(!cando[v[no][i]]){cando[v[no][i]]=1;q.push(v[no][i]);}
	}
	memcpy(er,cando,sizeof(cando));
	for(int i=1;i<=n;i++)
		if(!cando[i])
			for(int j=0,k=v[i].size();j<k;j++)
				if(er[v[i][j]])
					er[v[i][j]]=0;
	q.push(ed);
	while(!q.empty())
	{
		int no=q.front();
		q.pop();
		for(int i=0,j=v[no].size();i<j;i++)
			if(er[v[no][i]])
			{
				q.push(v[no][i]);
				er[v[no][i]]=0;
				ans[v[no][i]]=ans[no]+1;
			}
	}
	if(ans[st]==0)printf("-1");
	else printf("%d",ans[st]);
	return 0;
}