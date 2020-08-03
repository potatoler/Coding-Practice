#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
const int maxn=10010;
vector<int> g[maxn]; 
stack<int> st;  
int n,m,scc,ser;  
int low[maxn],dfn[maxn],instack[maxn],fa[maxn];  
int cnt[maxn];
void init(){  
    scc=ser=0;  
    while(!st.empty())st.pop();  
    for(int i=0;i<maxn;i++)g[i].clear();  
    memset(dfn,0,sizeof(dfn));  
    memset(instack,0,sizeof(instack));  
    memset(low,0,sizeof(low));
    memset(cnt,0,sizeof(cnt));
}  
void tarjan(int u){ 
    dfn[u]=low[u]=++ser;  
    instack[u]=1;  
    st.push(u);  
    int v,size=g[u].size();  
    for(int i=0;i<size;i++){
        v=g[u][i];  
        if(!dfn[v]){
            tarjan(v);  
            low[u]=min(low[u],low[v]);  
        }  
        else if(instack[v]) 
            low[u]=min(low[u],dfn[v]);  
    }  
    if(dfn[u]==low[u]){  
        scc++;  
        while(v!=u){  
            v=st.top();  
            st.pop();  
            fa[v]=scc;  
            instack[v]=0;  
        };  
    }  
}  
int main(){
	scanf("%d%d",&n,&m);
    init();
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<g[i].size();j++){
            int v=g[i][j];
            if(fa[i]!=fa[v]) cnt[fa[i]]++;
    	}
    int ans=0,u;
    for(int i=1;i<=scc;i++)
        if(!cnt[i]){
                u=i;
                ans++;
        }
	if(ans==1){
        ans=0;
	    for(int i=1;i<=n;i++)
            if(fa[i]==u) ans++;
            printf("%d\n",ans);
        }
        else printf("0\n");
    return 0;
}