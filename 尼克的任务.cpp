#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring> 
#include<algorithm>  
using namespace std;  
long int n,k,sum[10001],num=1,f[10001];  
struct tsk {  
    int ks,js;  
};  
tsk z[10001];  
int cmp(tsk a,tsk b){  
    return a.ks>b.ks;  
}  
int main()  {  
    cin>>n>>k;  
    for(int i=1;i<=k;i++){  
    cin>>z[i].ks>>z[i].js;    
    sum[z[i].ks]++;  
    }  
    sort(z+1,z+k+1,cmp);  
    for(int i=n;i>=1;i--){  
        if(sum[i]==0)  
        f[i]=f[i+1]+1;  
        else for(int j=1;j<=sum[i];j++){  
            if(f[i+z[num].js]>f[i])  
            f[i]=f[i+z[num].js];  
            num++;   
        }  
    }  
    cout<<f[1]<<endl;  
    return 0;
}