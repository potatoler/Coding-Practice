#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 998244353;
int n, m, a[MaxN], q, f[MaxN];
int degree[MaxN], k[MaxN], g[MaxN];
struct Operation{
	int type, pos, value;
	vector<int> func;
}op[MaxN];
int mul[MaxN];

inline int Read(){
	int num = 0, opt = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') opt = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * opt;
}

inline void Calculate(int x){
	if(mul[x] != -1) return;
	switch(op[x].type){
		case 1:{
			mul[x] = 1;
			break;
		}
		case 2:{
			mul[x] = op[x].value;
			break;
		}
		case 3:{
			mul[x] = 1;
			for(int i=0; i<op[x].func.size(); i++){
				int y = op[x].func[i];
				Calculate(y);
				mul[x] = mul[x] * mul[y] % Mod;
			}
			break;
		}
	}
}

inline void Topo(){
	queue<int> que;
	for(int i=1; i<=m; i++)
		if(degree[i] == 0) que.push(i);
	while(que.size()){
		int x = que.front();
		que.pop();
		switch(op[x].type){
			case 1:{
				k[op[x].pos] = (k[op[x].pos] + g[x] * op[x].value) % Mod;
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				for(int j=op[x].func.size()-1; j>=0; j--){
					int y = op[x].func[j];
					g[y] = (g[x] + g[y]) % Mod;
					g[x] = g[x] * mul[y] % Mod;
					if(--degree[y] == 0) que.push(y);
				}
				break;
			}
		}
	}
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	m = Read();
	for(int i=1; i<=m; i++){
		op[i].type = Read();
		switch(op[i].type){
			case 1:{
				op[i].pos = Read();
				op[i].value = Read();
				break;
			}
			case 2:{
				op[i].value = Read();
				break;
			}
			case 3:{
				int cnt = Read();
				while(cnt--){
					int x = Read();
					op[i].func.push_back(x);
				}
				break;
			}
		}
	}
	memset(mul, -1, sizeof(mul));
	for(int i=1; i<=m; i++)
		if(mul[i] == -1) Calculate(i);
	q = Read();
	for(int i=1; i<=q; i++)
		f[i] = Read();
	int b = 1;
	for(int i=q; i>=1; i--){
		switch(op[f[i]].type){
			case 1:{
				g[f[i]] = (g[f[i]] + b) % Mod;
				break;
			}
			case 2:{
				b = b * op[f[i]].value % Mod;
				break;
			}
			case 3:{
				g[f[i]] = (g[f[i]] + b) % Mod;
				b = b * mul[f[i]] % Mod;
				break;
			}
		}
	}
	for(int i=1; i<=m; i++){
		if(op[i].type != 3) continue;
		for(int j=0; j<op[i].func.size(); j++){
			int y = op[i].func[j];
			degree[y]++;
		}
	}
	Topo();
	for(int i=1; i<=n; i++)
		printf("%lld ", (a[i] * b + k[i]) % Mod);
	return 0;
}