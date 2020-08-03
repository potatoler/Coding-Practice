#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define maxn (100000+500)
#define inf 2000000005
using namespace std;
int sum=0,R=0;
int size[maxn],v[maxn],num[maxn],rd[maxn],son[maxn][2];

void pushup(int p)
{
	size[p]=size[son[p][0]]+size[son[p][1]]+num[p];
}

void rotate(int &p,int d)
{
	int k=son[p][d^1];
	son[p][d^1]=son[k][d];
	son[k][d]=p;
	pushup(p);
	pushup(k);
	p=k;
}

void ins(int &p,int x)
{
	if (!p)
	{
		p=++sum;
		size[p]=num[p]=1;
		v[p]=x;
		rd[p]=rand();
		return;
	}
	if (v[p]==x)
	{
		num[p]++;
		size[p]++;
		return;
	}
	int d=(x>v[p]);
	ins(son[p][d],x);
	if (rd[p]<rd[son[p][d]]) rotate(p,d^1);
	pushup(p);
}

void del(int &p,int x)
{
	if (!p) return;
	if (x<v[p]) del(son[p][0],x);
	else if (x>v[p]) del(son[p][1],x);
	else
	{
		if (!son[p][0] && !son[p][1])
		{
			num[p]--; size[p]--; 
			if (num[p]==0) p=0;
		} 
		else if (son[p][0] && !son[p][1])
		{
			rotate(p,1);
			del(son[p][1],x);
		}
		else if (!son[p][0] && son[p][1])
		{
			rotate(p,0);
			del(son[p][0],x);
		}
		else if (son[p][0] && son[p][1])
		{
			int d=(rd[son[p][0]]>rd[son[p][1]]);
			rotate(p,d);
			del(son[p][d],x);
		}
	}
	pushup(p);
}

int rk(int p,int x)
{
	if (!p) return 0;
	if (v[p]==x) return size[son[p][0]]+1;
	else if (v[p]<x) return size[son[p][0]]+num[p]+rk(son[p][1],x);
	else return rk(son[p][0],x);
}

int find(int p,int x)
{
	if (!p) return 0;
	if (size[son[p][0]]>=x) return find(son[p][0],x);
	else if (size[son[p][0]]+num[p]<x)
		return find(son[p][1],x-num[p]-size[son[p][0]]);
	else return v[p];
}

int pre(int p,int x)
{
	if (!p) return -inf;
	if (v[p]>=x) return pre(son[p][0],x);
	else return max(v[p],pre(son[p][1],x));
}

int suc(int p,int x)
{
	if (!p) return inf;
	if (v[p]<=x) return suc(son[p][1],x);
	else return min(v[p],suc(son[p][0],x));
}

int main()
{
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;++i)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if (opt==1) ins(R,x);
		else if (opt==2) del(R,x);
		else if (opt==3) printf("%d\n",rk(R,x));
		else if (opt==4) printf("%d\n",find(R,x));
		else if (opt==5) printf("%d\n",pre(R,x));
		else if (opt==6) printf("%d\n",suc(R,x));
	}

	return 0;
}