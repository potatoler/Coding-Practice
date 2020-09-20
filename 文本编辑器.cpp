#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int SqrtN = 2003;
int t, blockPos, charPos, queue[SqrtN], top;
char str[SqrtN*SqrtN], op[10];
struct Block{
	int len, pre, suc;
	char str[SqrtN];
}block[SqrtN];
#define nextBlock block[block[cur].suc]
#define lastBlock block[block[cur].pre]

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

inline void AddBlock(int old, int cur){
	block[cur].suc = block[old].suc;
	block[cur].pre = old;
	lastBlock.suc = cur;
	nextBlock.pre = cur;
	return;
}

inline void RemoveBlock(int cur){
	lastBlock.suc = block[cur].suc;
	nextBlock.pre = block[cur].pre;
	block[cur].len = block[cur].pre = block[cur].suc = 0;
	queue[++top] = cur;
	return;
}

inline void MergeBlock(){
	for(int cur = block[0].suc; cur; cur = block[cur].suc){
		while(block[cur].suc && block[cur].len + nextBlock.len < SqrtN){
			int suc = block[cur].suc;
			for(int j=block[cur].len, k=0; k < nextBlock.len; j++, k++)
				block[cur].str[j] = nextBlock.str[k];
			if(blockPos == suc){
				blockPos = cur;
				charPos += block[cur].len;
			}
			block[cur].len += nextBlock.len;
			RemoveBlock(suc);
		}
	}
}

inline void MOVE(int x){
	blockPos = block[0].suc;
	while(x > block[blockPos].len){
		x -= block[blockPos].len;
		blockPos = block[blockPos].suc;
	}
	charPos = x - 1;
	return;
}

inline void INSERT(int k){
	if(charPos < block[blockPos].len-1){
		int cur = queue[top--];
		for(int i = charPos+1; i < block[blockPos].len; i++){
			block[cur].str[block[cur].len] = block[blockPos].str[i];
			block[cur].len++;
		}
		block[blockPos].len = charPos + 1;
		AddBlock(blockPos, cur);
	}
	int now = blockPos, i = 0;
	while(i<k){
		int cur = queue[top--];
		while(block[cur].len < SqrtN && i < k){
			block[cur].str[block[cur].len] = str[i++];
			block[cur].len++;
		}
		AddBlock(now, cur);
		now = cur;
	}
	return;
}

inline void DELETE(int k){
	if(block[blockPos].len - 1 - charPos >= k){
		for(int i = charPos + k + 1, j = charPos + 1; i < block[blockPos].len; i++, j++)
			block[blockPos].str[j] = block[blockPos].str[i];
		block[blockPos].len -= k;
	}
	else{
		k -= block[blockPos].len- charPos - 1;
		block[blockPos].len = charPos + 1;
		while(block[blockPos].suc && k >= block[block[blockPos].suc].len){
			int cur = block[blockPos].suc;
			k -= block[cur].len;
			RemoveBlock(cur);
		}
		int cur = block[blockPos].suc;
		for(int i=0, j=k; j < block[cur].len; i++, j++)
			block[cur].str[i] = block[cur].str[j];
		block[cur].len -= k;
	}
	return;
}

inline void GET(int k){
	if(block[blockPos].len - 1 - charPos >= k){
		for(int i=0, j=charPos+1; i<k; i++, j++)
			putchar(block[blockPos].str[j]);
	}
	else{
		k -= block[blockPos].len - charPos - 1;
		for(int i = charPos+1; i < block[blockPos].len; i++)
			putchar(block[blockPos].str[i]);
		int now = blockPos;
		while(block[now].suc && k >= block[block[now].suc].len){
			int cur = block[now].suc;
			for(int i=0; i<block[cur].len; i++)
				putchar(block[cur].str[i]);
			k -= block[cur].len;
			now = cur;
		}
		int cur = block[now].suc;
		for(int i=0; i<k; i++)
			putchar(block[cur].str[i]);
	}
	printf("\n");
	return;
}

inline void PREV(){
	if(charPos) charPos--;
	else{
		blockPos = block[blockPos].pre;
		charPos = block[blockPos].len-1;
	}
	return;
}

inline void NEXT(){
	if(charPos < block[blockPos].len-1) charPos++;
	else{
		blockPos = block[blockPos].suc;
		charPos = 0;
	}
}

signed main(){
	t = Read();
	for(int i=1; i<SqrtN; i++)
		queue[++top] = i;
	str[0] = '~';
	INSERT(1);
	MOVE(1);
	while(t--){
		int var;
		scanf("%s", op);
		if(op[0] == 'M'){
			var = Read();
			MOVE(var+1);
		}
		else if(op[0] == 'I'){
			var = Read();
			int i = 0, k = var;
			while(var){
				str[i] = getchar();
				if(str[i] >= 32 && str[i] <= 126 && str[i] != '\n') i++, var--;
			}
			INSERT(k);
			MergeBlock();
		}
		else if(op[0] == 'D'){
			var = Read();
			DELETE(var);
			MergeBlock();
		}
		else if(op[0] == 'G'){
			var = Read();
			GET(var);
		}
		else if(op[0] == 'P') PREV();
		else NEXT();
	}
	return 0;
}