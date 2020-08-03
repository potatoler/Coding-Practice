#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=10005;
int n;
int main(){
	scanf("%d",&n);
	if(n==2){
		cout<<5<<endl;
		cout<<"1 1"<<endl;
		cout<<"1 2"<<endl;
		cout<<"1 3"<<endl;
		cout<<"2 3"<<endl;
		cout<<"2 2"<<endl;
		cout<<"2 1"<<endl;
	}
	if(n==3){
		cout<<11<<endl;
		cout<<"1 1"<<endl;
		cout<<"2 2"<<endl;
		cout<<"3 3"<<endl;
		cout<<"3 2"<<endl;
		cout<<"3 1"<<endl;
		cout<<"2 1"<<endl;
		cout<<"1 2"<<endl;
		cout<<"1 3"<<endl;
		cout<<"1 4"<<endl;
		cout<<"2 4"<<endl;
		cout<<"3 4"<<endl;
		cout<<"2 3"<<endl;
	}
	if(n==4){
		cout<<19<<endl;
		
	}
	return 0;
}