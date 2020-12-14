#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
const int MaxLength = 55;

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

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * op + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	return 0;
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