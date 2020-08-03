#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
char  a[100005],b[100005];
bool cmp(string a,string b){
	int i,j;
	for (i=0,j=0;i<a.length() && j<b.length();){
		if (a[i]==b[j]||abs(a[i]-b[j])==32)	i++,j++;
		else if (a[i]==32) i++;
		else if (b[j]==32) j++;
		else return false;
	}
	return true;
}
int main(){
	cin.getline(a,100005);
	cin.getline(b,100005);
	if(cmp(a,b))
		printf("YES");
	else
		printf("NO");
	return 0;
}
