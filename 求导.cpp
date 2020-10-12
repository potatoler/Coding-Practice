#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
#define Plus 1
#define Minus 2
#define Multiplication 3
#define Sine 4
#define Cosine 5
#define Power 6
#define Negative 7
#define Variable 8
#define Constant 9
const int MaxN = 102, Mod = 998244353;
char str[MaxN];
int q, stack[MaxN], top, cntTree, X;
int inv[6] = {0, 1, 499122177, 166374059, 291154603, 856826403};
struct ExpressionTree{
	int son[2], value, type, next;
}tree[MaxN];
#define thisTree tree[cur]
struct Answer{
	int fx, dx;
};

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

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

inline int Sin(int x){
	return (((x - x*x % Mod * x % Mod * inv[3] % Mod) % Mod + Mod) % Mod + x*x % Mod * x % Mod * x % Mod * x % Mod * inv[5] % Mod) % Mod;
}

inline int Cos(int x){
	return (((1 - x*x % Mod * inv[2] % Mod) % Mod + Mod) % Mod + x*x % Mod * x % Mod * x % Mod * inv[4] % Mod) % Mod;
}

inline int Build(int l, int r){
	if(l == r && str[l] == 'x'){
		tree[++cntTree].type = Variable;
		return cntTree;
	}
	
	if(str[l] == '(' && str[r] == ')' && tree[l].next == r + 1) return Build(l+1, r-1);
	
	int pls = 0, mul = 0, pwr = 0;
	for(int i=l; i<=r; i = tree[i].next){
		if(str[i] == '+' || str[i] == '-') pls = i;
		else if(str[i] == '*') mul = i;
		else if(str[i] == '^') pwr = i;
	}
	
	int cur = ++cntTree;
	
	if(pls){
		if(str[pls] == '+'){
			thisTree.type = Plus;
			thisTree.son[0] = Build(l, pls-1);
			thisTree.son[1] = Build(pls+1, r);
			return cur;
		}
		else{
			if(pls == l){
				thisTree.type = Negative;
				thisTree.son[0] = Build(l+1, r);
				return cur;
			}
			else{
				thisTree.type = Minus;
				thisTree.son[0] = Build(l, pls-1);
				thisTree.son[1] = Build(pls+1, r);
				return cur;
			}
		}
	}
	
	else if(mul){
		thisTree.type = Multiplication;
		thisTree.son[0] = Build(l, mul-1);
		thisTree.son[1] = Build(mul+1, r);
		return cur;
	}
	
	else if(pwr){
		thisTree.type = Power;
		thisTree.son[0] = Build(l, pwr-1);
		int p = 0;
		for(int i=pwr+1; i<=r; i++)
			p = p * 10 + str[i] - '0';
		thisTree.value = p;
		return cur;
	}
	
	else if(str[l] == 's'){
		thisTree.type = Sine;
		thisTree.son[0] = Build(l+4, r-1);
		return cur;
	}
	
	else if(str[l] == 'c'){
		thisTree.type = Cosine;
		thisTree.son[0] = Build(l+4, r-1);
		return cur;
	}
	
	else{
		int num = 0;
		for(int i=l; i<=r; i++)
			num = num * 10 + str[i] - '0';
		thisTree.type = Constant;
		thisTree.value = num % Mod;
		return cur;
	}
}

inline Answer Calculate(int cur){
	Answer res, ls, rs;
	
	if(thisTree.type == Variable){
		res.dx = 1;
		res.fx = X;
		return res;
	}
	
	else if(thisTree.type == Constant){
		res.dx = 0;
		res.fx = thisTree.value;
		return res;
	}
	
	if(thisTree.son[0]) ls = Calculate(thisTree.son[0]);
	if(thisTree.son[1]) rs = Calculate(thisTree.son[1]);
	
	if(thisTree.type == Plus){
		res.dx = (ls.dx + rs.dx) % Mod;
		res.fx = (ls.fx + rs.fx) % Mod;
		return res;
	}
	
	else if(thisTree.type == Minus){
		res.dx = (ls.dx - rs.dx + Mod) % Mod;
		res.fx = (ls.fx - rs.fx + Mod) % Mod;
		return res;
	}
	
	else if(thisTree.type == Multiplication){
		res.dx = (ls.dx * rs.fx % Mod + ls.fx * rs.dx % Mod) % Mod;
		res.fx = ls.fx * rs.fx % Mod;
		return res;
	}
	
	else if(thisTree.type == Sine){
		res.dx = ls.dx * Cos(ls.fx) % Mod;
		res.fx = Sin(ls.fx) % Mod;
		return res;
	}
	
	else if(thisTree.type == Cosine){
		res.dx = (Mod - ls.dx) * Sin(ls.fx) % Mod;
		res.fx = Cos(ls.fx);
		return res;
	}
	
	else if(thisTree.type == Power){
		res.dx = thisTree.value * ls.dx % Mod * QuickPower(ls.fx, thisTree.value-1) % Mod;
		res.fx = QuickPower(ls.fx, thisTree.value);
		return res;
	}
	
	else if(thisTree.type == Negative){
		res.dx = (Mod-1) * ls.dx % Mod;
		res.fx = (Mod-1) * ls.fx % Mod;
		return res;
	}
	return res;
}

signed main(){
	scanf("%s", str+1);
	int len = strlen(str+1);
	q = Read();
	for(int i=1; i<=len; i++){
		tree[i].next = i+1;
		if(str[i] == '(') stack[++top] = i;
		if(str[i] == ')') tree[stack[top--]].next = i+1;
	}
	int root = Build(1, len);
	while(q--){
		int op = Read();
		X = Read();
		Answer ans = Calculate(root);
		if(op) printf("%lld\n", ans.dx);
		else printf("%lld\n", ans.fx);
	}
//	printf("%lld\n", root);
	return 0;
}