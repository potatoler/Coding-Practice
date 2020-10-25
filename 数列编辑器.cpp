#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define lowbit(x) x&(-x)
#define int long long
using namespace std;
const int MaxN = 300005;

class BIT{
	private:
		
	int stack[MaxN], array[MaxN], top, length;
	
	inline void Add(int p, int x){
		while(p<=length){
			array[p] += x;
			p += lowbit(p);
		}
		return;
	}
	
	inline int Pre_Sum(int p){
		int sum = 0;
		while(p){
			sum += array[p];
			p -= lowbit(p);
		}
		return sum;
	}
	
	public:
		
	inline void Build(int n){
		length = n;
		top = 0;
		memset(stack, 0, sizeof(stack));
		memset(array, 0, sizeof(array));
	}
	
	inline void Push(int x){
		top++;
		Add(top, x);
		stack[top] = x;
		return;
	}
	
	inline void Pop(){
		Add(top, -stack[top]);
		stack[top--] = 0;
		return;
	}
	
	inline int Top(){
		return stack[top];
	}
	
	inline void Change(int p, int x){
		Add(p, x-stack[p]);
		stack[p] = x;
	}
	
	inline int Sum(int l, int r){
		return Pre_Sum(r) - Pre_Sum(l-1);
	}
	
	inline int Size(){
		return top;
	}
};

int n;
BIT pre, suf;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
//	freopen("editor.in", "r", stdin);
//	freopen("editor.out", "w", stdout);
	n = Read();
	pre.Build(n), suf.Build(n);
	char op[5];
	for(int i=1; i<=n; i++){
		scanf("%s", op);
		switch(op[0]){
			case 'I':{
				int x = Read();
				pre.Push(x);
				break;
			}
			case 'D':{
				pre.Pop();
				break;
			}
			case 'L':{
				if(pre.Size()){
					suf.Push(pre.Top());
					pre.Pop();
				}
				break;
			}
			case 'R':{
				if(suf.Size()){
					pre.Push(suf.Top());
					suf.Pop();
				}
				break;
			}
			case 'Q':{
				int l = Read(), r = Read();
				int preSize = pre.Size(), sufSize = suf.Size();
				if(r <= preSize) printf("%lld\n", pre.Sum(l, r));
				else{
					if(l > preSize) printf("%lld\n", suf.Sum(sufSize-(r-preSize-1), sufSize-(l-preSize-1)));
					else printf("%lld\n", pre.Sum(l, preSize) + suf.Sum(sufSize-(r-preSize-1), sufSize));
				}
				break;
			}
			case 'C':{
				int p = Read(), x = Read();
				int preSize = pre.Size(), sufSize = suf.Size();
				if(p <= preSize) pre.Change(p, x);
				else suf.Change(sufSize-(p-preSize-1), x);
				break;
			}
		}
	}
	return 0;
}