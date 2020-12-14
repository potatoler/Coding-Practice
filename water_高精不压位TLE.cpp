#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
//#define int long long
using namespace std;
const int MaxN = 100005, MaxLength = 128;
int n, m, head[MaxN], cntEdge, ind[MaxN], outd[MaxN];
int stack[MaxN], top;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*20];

class BigInt{
public:
	int d[MaxLength], len;
	
	BigInt(){
		memset(d, 0, sizeof(d));
		len = 1;
	}
	BigInt(int num){
		*this = num;
	};
	BigInt(char* str){
		*this = str;
	}
	string Str() const;
	void Clear0();
	void Reset();
	void Read();
	BigInt operator = (const char*);
	BigInt operator = (int);
	BigInt operator + (const BigInt&);
	BigInt operator - (const BigInt&);
	BigInt operator * (const BigInt&) const;
	BigInt operator / (const BigInt&);
	BigInt operator % (const BigInt&);
	BigInt operator += (const BigInt& that) {return *this = *this + that;}
	BigInt operator -= (const BigInt& that) {return *this = *this - that;}
	BigInt operator *= (const BigInt& that) {return *this = *this * that;}
	BigInt operator /= (const BigInt& that) {return *this = *this / that;}
	BigInt operator %= (const BigInt& that) {return *this = *this % that;}
	bool operator < (const BigInt&) const;
	bool operator > (const BigInt& that) const {return that < *this;}
	bool operator <= (const BigInt& that) const {return !(that < *this);}
	bool operator >= (const BigInt& that) const {return !(*this < that);}
	bool operator != (const BigInt& that) const {return *this < that || that < *this;}
	bool operator == (const BigInt& that) const {return !(*this < that) && !(that < *this);}
};

istream& operator >> (istream& in, BigInt& x);
ostream& operator << (ostream& out, const BigInt& x);

inline BigInt GCD(BigInt a, BigInt b){
	return b==0 ? a : GCD(b, a%b);
}

class Fraction{
	public:
	BigInt up, down;
	Fraction operator + (const Fraction&);
	Fraction operator * (const Fraction&);
	Fraction operator / (const BigInt);
	
	inline void Init(BigInt num = 0){
		down = 1;
		up = num;
		return;
	}
	
	inline void Print(){
		cout<<up<<' '<<down<<endl;
		return;
	}
}val[MaxN];

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

inline Fraction FRead(){
	BigInt up, down;
	cin>>up>>down;
	return (Fraction){up, down};
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	ind[v]++;
	outd[u]++;
	return;
}

inline void Topo(){
	queue<int> q;
	bool visited[MaxN];
	for(int i=1; i<=m; i++)
		q.push(i), visited[i] = true;
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(y == true) continue;
			val[y] = val[y] + val[x] / BigInt(outd[x]);
			ind[y]--;
			if(!ind[y]) q.push(y), visited[y] = true;
		}
	}
	return;
}

signed main(){
	std::ios::sync_with_stdio(false); 
	std::cin.tie(0);
	freopen("water.in", "r", stdin);
	freopen("water.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		val[i].Init();
		int d = Read();
		for(int j=1; j<=d; j++){
			int a = Read();
			AddEdge(i,a);
		}
	}
	for(int i=1; i<=m; i++)
		val[i].Init(1);
	for(int i=1; i<=n; i++)
		if(!outd[i]) stack[++top] = i;
	Topo();
	for(int i=1; i<=top; i++)
		val[stack[i]].Print();
}

void BigInt::Read(){
	string str;
	cin>>str;
	*this = str.c_str();
	return;
}

void BigInt::Clear0(){
	while(len > 1 && !d[len-1])
		len--;
	return;
}

BigInt BigInt::operator = (const char* str){
	memset(d, 0, sizeof(d));
	len = strlen(str);
	for(int i=0; i<len; i++)
		d[i] = str[len-1-i] - '0';
	Clear0();
	return *this;
}

BigInt BigInt::operator = (int num){
	char str[MaxLength];
	sprintf(str, "%d", num);
	*this = str;
	return *this;
}

BigInt BigInt::operator + (const BigInt& that){
	BigInt self = *this;
	int i;
	for(i=0; i<that.len; i++){
		self.d[i] += that.d[i];
		if(self.d[i] > 9){
			self.d[i] %= 10;
			self.d[i+1]++;
		}
	}
	while(self.d[i] > 9){
		self.d[i] %= 10;
		self.d[++i]++;
	}
	self.len = max(self.len, that.len);
	if(self.d[i] && self.len <= i) self.len = i+1;
	return self;
}

BigInt BigInt::operator - (const BigInt& that){
	BigInt self = *this;
	int i;
	for(i=0; i<that.len; i++){
		self.d[i] -= that.d[i];
		if(self.d[i] < 0){
			self.d[i] += 10;
			self.d[i+1]--;
		}
	}
	while(self.d[i] < 0){
		self.d[i++] += 10;
		self.d[i]--;
	}
	self.Clear0();
	return self;
}

BigInt BigInt::operator * (const BigInt& that) const {
	BigInt res, self = *this;
	res.len = self.len + that.len;
	int i,j;
	for(j=0; j<that.len; j++)
		for(i=0; i<self.len; i++)
		res.d[i+j] += self.d[i] * that.d[j];
	for(i=0; i<res.len-1; i++){
		res.d[i+1] += res.d[i] / 10;
		res.d[i] %= 10;
	}
	res.Clear0();
	return res;
}

BigInt BigInt::operator / (const BigInt& that){
	int i,j;
	BigInt self = *this, rem = 0;
	for(i = self.len-1; i>=0; i--){
		rem = rem * 10 + self.d[i];
		for(j=0; j<10; j++)
			if(rem < that * (j+1)) break;
		self.d[i] = j;
		rem = rem - that * j;
	}
	self.Clear0();
	return self;
}

BigInt BigInt::operator % (const BigInt& that){
	int i, j;
	BigInt self = *this, rem = 0;
	for(i = self.len-1; i>=0; i--){
		rem = rem * 10 + self.d[i];
		for(j=0; j<10; j++)
			if(rem < that * (j+1)) break;
		rem = rem - that * j;
	}
	return rem;
}

bool BigInt::operator < (const BigInt& that) const {
	BigInt self = *this;
	if(self.len != that.len) return self.len < that.len;
	for(int i = self.len-1; i>=0; i--)
		if(self.d[i] != that.d[i]) return self.d[i] < that.d[i];
	return false;
}

string BigInt::Str() const{
	char str[MaxLength] = {};
	for(int i=0; i<len; i++)
		str[len-1-i] = d[i] + '0';
	return str;
}

istream& operator >> (istream& in, BigInt& x){
	string str;
	in >> str;
	x = str.c_str();
	return in;
}

ostream& operator << (ostream& out, const BigInt& x){
	out << x.Str();
	return out;
}

Fraction Fraction::operator + (const Fraction& y){
//	BigInt resup = up*y.down + y.up*down;
//	BigInt resdown = down * y.down;
//	BigInt gcd = GCD(resup, resdown);
//	return (Fraction){resup/gcd, resdown/gcd};
	BigInt yd = y.down;
	BigInt gcd = GCD(down, y.down);
	BigInt resup = down / gcd * y.up + yd / gcd * up;
	BigInt resdown = down / gcd * y.down;
	BigInt gcd2 = GCD(resup, resdown);
	return (Fraction){resup/gcd2, resdown/gcd2};
}

Fraction Fraction::operator * (const Fraction& y){
	BigInt resup = up*y.up;
	BigInt resdown = down*y.down;
	BigInt gcd = GCD(resup, resdown);
	return (Fraction){resup/gcd, resdown/gcd};
}

Fraction Fraction::operator / (const BigInt y){
	BigInt resup = up;
	BigInt resdown = down*y;
	BigInt gcd = GCD(resup, resdown);
	return (Fraction){resup/gcd, resdown/gcd};
}