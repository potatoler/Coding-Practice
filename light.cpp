#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 5000006;
int T, n, k;
char str[MaxN];
class Deque{
	private:
	int storage[MaxN];
	
	public:
	int head, tail;
	
	inline void Clear(){
		head = tail = 1;
		storage[head] = 0;
		return;
	}
	
	inline bool Empty(){
		return head > tail;
	}
	
	inline void Pushback(int x){
		storage[++tail] = x;
		return;
	}
	inline int Back(){
		return storage[tail];
	}
	inline void PopBack(){
		storage[tail--] = 0;
		return;
	}
	
	inline void PushFront(int x){
		storage[--head] = x;
		return;
	}
	inline int Front(){
		return storage[head];
	}
	inline void PopFront(){
		storage[head++] = 0;
		return;
	}
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

inline void Solve(){
	int f[MaxN];
	Deque q1, q2;
	q1.Clear();
	q2.head = 1, q2.tail = 0;
	for(int i=1; i<=n; i++){
		f[i] = f[i-1] + i;
		if(str[i] == '1') q2.Pushback(i);
		while(!q2.Empty() && q2.Front() + k < i)
			q2.PopFront();
		if(!q2.Empty()){
			while(!q1.Empty() && q1.Front() < q2.Front()-k-1)
				q1.PopFront();
			if(!q1.Empty()) f[i] = min(f[i], f[q1.Front()] + q2.Front());
		}
		while(!q1.Empty() && f[q1.Back()] >= f[i]) q1.PopBack();
		q1.Pushback(i);
	}
	printf("%lld\n", f[n]);
	return;
}

signed main(){
	T = Read();
	while(T--){
		n = Read(), k = Read();
		scanf("%s", str+1);
		Solve();
	}
	return 0;
}