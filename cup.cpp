#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1005
const int eps = 0.00001;
double a[N],lis[N];
int r[N],l[N],n;
int bin_search(int left,int right,double x)
{
    int mid;
    while(left <= right)
    {
        mid = left+(right-left)/2;
        if(lis[mid] > x) right = mid-1;
        else if(lis[mid] < x) left = mid+1;
        else return mid;
    }
    return left;
}
int main()
{
//    freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%lf",&a[i]);
        int index,len;
        len = 1;
        lis[0] = a[0];
        l[0] = 1;
        for(int i=1;i<n;i++)
        {
            if(a[i] > lis[len-1]) lis[len] = a[i],len++,l[i] = len;   //两个边界情况就不用二分找了
            else if(a[i] < lis[0]) lis[0] = a[i],l[i] = 1;       //直接维护就行
            else
            {
                index = bin_search(0,len,a[i]);
                lis[index] = a[i];
                if(index > len) len++;
                l[i] = index+1;
            }
        }
        lis[0] = a[n-1];
        r[n-1] = 1;
        len = 1;
        for(int i=n-2;i>-1;i--)
        {
            if(a[i] > lis[len-1]) lis[len] = a[i],len++,r[i] = len;
            else if(a[i] < lis[0]) lis[0] = a[i],r[i] = 1;
            else
            {
                index = bin_search(0,len,a[i]);
                lis[index] = a[i];
                if(index > len) len++;
                r[i] = index+1;
            }
        }
        int ans = -1;
        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                if(l[i]+r[j] > ans) ans = l[i]+r[j];
        printf("%d\n",n-ans);
    }
    return 0;
}