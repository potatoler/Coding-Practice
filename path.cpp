#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=105;
bool map[maxn][maxn];
int path[maxn];
stack<int>s;
int n;
int cnt;
void dfs(int x){
    s.push(x);
    for(int i=1;i<=n;i++){
        if(map[x][i]>0){
            map[i][x]=map[x][i]=0;
            dfs(i);
            break;
        }
    }
}
void Fleury(int v){
    while(!s.empty())
        s.pop();
    s.push(v);
    while(!s.empty()){
        int b = 0;
        for(int i=1;i<=n;i++){
            if(map[s.top()][i]>0){
                b = 1;
                break;
            }
        }
        if(b == 0){
            path[cnt++] = s.top();
            s.pop();
        }
        else{
            int y = s.top();
            s.pop();
            dfs(y);
        }
    }
    cout<<endl;
}
 
int main(){
    int i,j,a,b;
    cin>>n;
    memset(map,0,sizeof(map));
    for(int i=1;i<n;i++) map[i][i+1]=1;
    for(int i=n;i<n*n;i+=n) map[i][i+n]=1;
    for(int i=1;i<n*n-n;i+=n) map[i+n][i]=1;
    for(int i=n;i>n*n-n+1;i--) map[i][i-1]=1;
    for(int i=1;i<=n;i++) map[i][i+n+1]=1,map[i][i+n-1]=1,map[i][i-n+1]=1,map[i][i-n-1]=1;
    int start = 1;
    int num = 0;
    for(i=1;i<=n;i++){
        int degree = 0;
        for(j=1;j<=n;j++){
            degree += map[i][j];
        }
        if(degree%2){
            if(num == 0)
                start = i;
            num++;
        }
    }
    cnt = 0;
    if(num==0 || num==2)
        Fleury(start);
    else
        cout<<-1<<endl;
    for(i=cnt-1;i>=0;i--){
        cout<<path[i]<<" ";
    }
    return 0;
}