#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
using namespace std;
#define int long long
const int Mod = 1e9+7, MaxN = 3e5+5;
int n, q, a, b, INV;
int A[MaxN][4];
struct SegmentTree{
	int l, r;
	int value[3][3], lazyTag[2], sum[2][3];
}seg[MaxN * 8];
struct Matrix{
	int row, column, data[3][3];
	Matrix(){
		row = column = 0;
		memset(data,0,sizeof(data));
	}
	inline void Clear(){
		row = column = 3;
		for(int i=0;i<3;i++)
			data[i][i]=1;
	}
	friend Matrix operator *(const Matrix x, const Matrix y) {
		Matrix ans;
		ans.row = x.row;
		ans.column = y.column;
		for(int i=0;i<ans.row;i++)
			for(int j=0;j<2;j++)
				for (int k=0;k<3;k++)
					ans.data[i][j] = (ans.data[i][j] + x.data[i][k] * y.data[k][j] % Mod) % Mod;
		ans.data[2][2] = 1;
		return ans;
	}
}power[34], first, second;

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans % Mod;
}

Matrix QuickPower(int k) {
	Matrix ans;
	int x=1;
	ans.Clear();
	while(k){
		if(k&1) ans = ans * power[x];
		k>>=1;
		x++;
	}	
	return ans;
}

inline void LoadData(int x){
	Matrix tmp = first * QuickPower(A[x][0]-2);
	A[x][1] = tmp.data[0][1];
	A[x][2] = tmp.data[0][0];
	return;
}

inline void Update(int x){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			seg[x].value[i][j] = (seg[x*2].value[i][j] + seg[x*2+1].value[i][j])%Mod;
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			seg[x].sum[i][j] = (seg[x*2].sum[i][j] + seg[x*2+1].sum[i][j])%Mod;
}

inline void Plus(int x,int l){
	for(int i=0;i<2;i++) 
		seg[x].sum[l][i] = seg[x].sum[l][i+1];
	seg[x].sum[l][2] = (seg[x].sum[l][1] + seg[x].sum[l][0] * a % Mod + b * (seg[x].r - seg[x].l + 1) % Mod) % Mod;
	if(l==0){
		for(int i=0;i<2;i++)
			for(int j=0;j<3;j++)
				seg[x].value[i][j]	= seg[x].value[i+1][j];
		for(int i=0;i<3;i++)
			seg[x].value[2][i] = (seg[x].value[1][i] + seg[x].value[0][i] * a % Mod + b * seg[x].sum[1][i] % Mod) % Mod;
	}
	if(l==1){
		for(int i=0;i<2;i++)
			for(int j=0;j<3;j++)
				seg[x].value[j][i] = seg[x].value[j][i+1];
		for(int i=0;i<3;i++)
			seg[x].value[i][2] = (seg[x].value[i][1] + seg[x].value[i][0] * a % Mod + b * seg[x].sum[0][i] % Mod) % Mod;
	}
	return;
}

inline void Minus(int x,int l){
	if(a==0){
		for(int i=1;i+1;i--)
			seg[x].sum[l][i+1] = seg[x].sum[l][i];
		seg[x].sum[l][0] = (seg[x].sum[l][1] - b * (seg[x].r - seg[x].l + 1) % Mod + Mod) % Mod;
		if(l==0){
			for(int i=1;i+1;i--)
				for(int j=0;j<3;j++)
					seg[x].value[i+1][j] = seg[x].value[i][j];
			for (int i=0;i<3;i++)
				seg[x].value[0][i] = (seg[x].value[1][i] - b * seg[x].sum[1][i] % Mod + Mod) % Mod;
		}
		if(l==1){
			for(int i=1;i+1;i--)
				for(int j=0;j<3;j++)
					seg[x].value[j][i+1] = seg[x].value[j][i];
			for (int i=0;i<3;i++)
			seg[x].value[i][0] = (seg[x].value[i][1] - b * seg[x].sum[0][i] % Mod + Mod) % Mod;
		}
		return;
	}
	else{
		for(int i=1;i+1;i--)
			seg[x].sum[l][i+1]=seg[x].sum[l][i];
		seg[x].sum[l][0]=((seg[x].sum[l][2] - seg[x].sum[l][1] - b * (seg[x].r - seg[x].l + 1) % Mod) % Mod * INV % Mod + Mod) % Mod;
		if(l==0){
			for(int i=1;i+1;i--)
				for(int j=0;j<3;j++)
					seg[x].value[i+1][j] = seg[x].value[i][j];
			for (int i=0;i<3;i++)
				seg[x].value[0][i] = ((seg[x].value[2][i] - seg[x].value[1][i] - b * seg[x].sum[1][i] % Mod) % Mod * INV % Mod + Mod) % Mod;
		}
		if(l==1){
			for(int i=1;i+1;i--)
				for(int j=0;j<3;j++)
					seg[x].value[j][i+1] = seg[x].value[j][i];
			for(int i=0;i<3;i++)
				seg[x].value[i][0] = ((seg[x].value[i][2] - seg[x].value[i][1]-b * seg[x].sum[0][i] % Mod) % Mod * INV % Mod + Mod) % Mod;
		}
		return;
	}
}

inline void PushDown(int x,int y,int z) {
	if(z > 0)
		for(int i=1;i<=z;i++) 
			Plus(x,y);
	if(z < 0)
		for(int i=-1;i>=z;i--)
			Minus(x,y);
	return;
}

inline void PassTag(int x) {
	for (int l=0;l<=1;l++){
		PushDown(x*2, l, seg[x].lazyTag[l]);
		PushDown(x*2+1, l, seg[x].lazyTag[l]);
		seg[x*2].lazyTag[l] += seg[x].lazyTag[l];
		seg[x*2+1].lazyTag[l] += seg[x].lazyTag[l];
		seg[x].lazyTag[l] = 0;
	}
	return;
}

inline void Build(int x,int l,int r) {
	seg[x].l = l, seg[x].r = r;
	if(l==r){
		for(int i=0;i<3;i++){
			seg[x].sum[0][i] = A[l-1][i+1];
			seg[x].sum[1][i] = A[l+1][i+1];
		}
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				seg[x].value[i][j] = seg[x].sum[0][i] * seg[x].sum[1][j] % Mod;
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	Update(x);
}

inline void Add(int x,int ql,int qr,int y,int z) {
	if (seg[x].l > qr || seg[x].r < ql) return;
	if (ql <= seg[x].l && seg[x].r <= qr){
		seg[x].lazyTag[y] += z;
		PushDown(x,y,z);
		return;
	}
	PassTag(x);
	Add(x*2, ql, qr, y, z);
	Add(x*2+1, ql, qr, y, z);
	Update(x);
}

inline int Query(int x,int ql,int qr){
	int l = seg[x].l, r = seg[x].r;
	if(seg[x].l > qr || seg[x].r < ql) return 0;
	if(ql <= seg[x].l && seg[x].r <= qr) return seg[x].value[2][0];
	PassTag(x);
	return (Query(x*2, ql, qr) + Query(x*2+1, ql, qr)) % Mod;
}

signed main(){
	n = read(), q = read(), a = read(), b = read();
	INV = QuickPower(a,Mod-2);
	first.row = 1; first.column = 3;
	first.data[0][0] = 2; first.data[0][1] = 1; first.data[0][2] = 1;
	second.row = second.column=3;
	second.data[0][0] = 1; second.data[1][0] = a; second.data[2][0] = b;
	second.data[0][1] = 1; second.data[2][2] = 1;
	for(int i=1;i<=32;i++){
		power[i] = second;
		second = second * second;
	}
	for (int i=1;i<=n;i++) {
		scanf("%lld", A[i]);
		LoadData(i);
		A[i][3] = (A[i][2] + A[i][1] * a + b) % Mod;
	}
	Build(1,2,n-1);
	char op[10];
	while(q--) {
		int l,r;
		scanf("%s", op);
		switch(op[0]){
			case 'p':{
				l = read(), r = read();
				Add(1,l+1,r+1,0,1);
				Add(1,l-1,r-1,1,1);
				break;
			}
			case 'm':{
				l = read(), r = read();
				Add(1,l+1,r+1,0,-1);
				Add(1,l-1,r-1,1,-1);
				break;
			}
			case 'q':{
				l = read(), r = read();
				printf("%lld\n", Query(1,l+1,r-1));
				break;
			}
			default:{
				break;
			}
		}
	}
	return 0;
}