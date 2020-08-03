#include<iostream>
#include<cstdlib> 
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=1000005;
int n,m;
struct Meizi{
    int l,r,sum,mn,mx,atag,ctag;
}mz[maxn*4];
void pushup(int k){
    mz[k].sum=mz[k*2].sum+mz[k*2+1].sum;
    mz[k].mn=min(mz[k*2].mn,mz[k*2+1].mn);
    mz[k].mx=max(mz[k*2].mx,mz[k*2+1].mx);
 }
void build(int k,int l,int r){
    mz[k].ctag=-1,mz[k].l=l,mz[k].r=r;
    if(l==r){
        scanf("%d",&mz[k].sum);
        mz[k].mn=mz[k].mx=mz[k].sum;
        return;
    }
    int mid=(l+r)/2;
    build(k*2,l,mid),build(k*2+1,mid+1,r);
    pushup(k);
}
void pushdown(int k){
     int a=mz[k].atag,c=mz[k].ctag,x=mz[k].r-mz[k].l+1;
     if(c!=-1){
        mz[k*2].ctag=mz[k*2+1].ctag=c;
        mz[k*2].atag=mz[k*2+1].atag=0;
        mz[k*2].sum=c*(x-(x/2));
        mz[k*2+1].sum=c*(x/2);
        mz[k*2].mn=mz[k*2+1].mn=mz[k*2].mx=mz[k*2+1].mx=c;
        mz[k].ctag=-1;
     }
     if(a!=0){
        mz[k*2].atag+=a;mz[k*2+1].atag+=a;
        mz[k*2].sum+=a*(x-(x/2));mz[k*2+1].sum+=a*(x/2);
        mz[k*2].mn+=a;mz[k*2+1].mn+=a;
        mz[k*2].mx+=a;mz[k*2+1].mx+=a;
        mz[k].atag=0;
     }
}
void change(int k,int x,int y,int z){
	 pushdown(k);
     int l=mz[k].l,r=mz[k].r;
     if(l==x&&y==r){
		if(l!=r)mz[k].ctag=z;
		mz[k].mn=mz[k].mx=z;
		mz[k].sum=(r-l+1)*z;
        return;
    }
    int mid=(l+r)/2;
    if(mid>=y)change(k*2,x,y,z);
    else if(mid<x)change(k*2+1,x,y,z);
    else {
        change(k*2,x,mid,z);
        change(k*2+1,mid+1,y,z);}
    pushup(k);
}
void add(int k,int x,int y,int z){
	pushdown(k);
    int l=mz[k].l,r=mz[k].r;
    if(l==x&&y==r){
	   if(l!=r)mz[k].atag=z;
	   mz[k].sum+=(r-l+1)*z;
	   mz[k].mn+=z;mz[k].mx+=z;
	   return;
    }
    int mid=(l+r)/2;
    if(mid>=y)add(k*2,x,y,z);
    else if(mid<x)add(k*2+1,x,y,z);
    else{
        add(k*2,x,mid,z);
        add(k*2+1,mid+1,y,z);
    }
    pushup(k);
}
int ask(int k,int x,int y,int f){
    pushdown(k);
    int l=mz[k].l,r=mz[k].r;
    if(l==x&&r==y){
        if(f==1)return mz[k].sum;
        else if(f==2)return mz[k].mn;
        else return mz[k].mx;
    }
    int mid=(l+r)/2;
    if(mid>=y)return ask(k*2,x,y,f);
    else if(mid<x)return ask(k*2+1,x,y,f);
    else{
        if(f==1) return (ask(k*2,x,mid,f)+ask(k*2+1,mid+1,y,f));
        else if(f==2) return min(ask(k*2,x,mid,f),ask(k*2+1,mid+1,y,f));
        else return max(ask(k*2,x,mid,f),ask(k*2+1,mid+1,y,f));
    }
}
int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int c,dir,x,y,v;
        scanf("%d",&c);
        if(c==1){
            scanf("%d%d%d",&dir,&x,&y);
            printf("%d\n",ask(1,x,y,dir));
        }
        else{
             scanf("%d%d%d%d",&dir,&x,&y,&v);
             if(dir==1) add(1,x,y,v);
             else change(1,x,y,v); 
        }
    }
    return 0;
}