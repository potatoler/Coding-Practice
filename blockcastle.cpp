#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
bool s[101][10001];
int n,h;
int max,maxi;
int main (){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        s[i][0]=1;
        while(cin>>h&&h!=-1)
            for(int j=10000;j>=0;--j)
                if(s[i][j]==1) s[i][j+h]=1;
    }

    for(int j=5052;j>=1;--j){
        maxi=0;
        for(int i=1;i<=n;i++){
            if(s[i][j]==1) maxi++;
            if(maxi==n){
                printf("%d",j);
                return 0;
            }
        }
    }
    printf("0");
    return 0;
}