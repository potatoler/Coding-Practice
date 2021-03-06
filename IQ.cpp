#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct edge
{
 int v,w,next;
}e[10005];
int head[5005],tot[5005],dis[5005],vis[5005],cnt,n,m;
void add(int u,int v,int w)
{
 e[++cnt].v=v;
 e[cnt].w=w;
 e[cnt].next=head[u];
 head[u]=cnt;
}
bool spfa(int s)
{
 queue<int> q;
 memset(dis,63,sizeof(dis));
 dis[s]=0,vis[s]=1;
 q.push(s);
 while(!q.empty())
 {
  int u=q.front();
  q.pop();
  vis[u]=0;
  for(int i=head[u];i;i=e[i].next)
  {
   int v=e[i].v;
   if(dis[v]>dis[u]+e[i].w)
   {
    dis[v]=dis[u]+e[i].w;
    if(!vis[v])
    {
     vis[v]=1,tot[v]++;
     if(tot[v]==n)return false;
     q.push(v);
    }
   }
  }
 }
 return true;
}
int main()
{
 cin>>n>>m;
 for(int i=1;i<=n;i++)
  add(0,i,0);
 for(int i=1;i<=m;i++){
    int op,a,b;
    scanf("%d%d%d",&op,&a,&b);
    switch(op){
      case 1: add(b,a,0),add(a,b,0);
      case 2: add(b,a,-1);
      case 3: add(a,b,0);
      case 4: add(a,b,-1);
      case 5: add(b,a,0);
    } 
  }
 if(!spfa(0))cout<<"NO"<<endl;
 else
  for(int i=1;i<=n;i++)
   cout<<dis[i]<<' ';
 return 0;
}