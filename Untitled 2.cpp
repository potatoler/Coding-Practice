#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define id(x,y) ((x)*m+(y))
#define min(a,b) ((a)<(b)? (a):(b))
const int inf=0x3f3f3f3f;
int cnt=0;
int a[105],vis[105],mp[105],b[105][1<<10],f[105][1<<10],pre[105][1<<10];
int h[105],to[2005],ver[2005];
std::priority_queue<std::pair<int,int> > Q;

inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;

}
//inline void add(int x,int y) {
//	to[++cnt]=y;
//	ver[cnt]=h[x];
//	h[x]=cnt;
//}

inline void add(int u, int v){
	cnt++;
	to[cnt] = v;
	ver[cnt] = h[u];
	h[u] = cnt;
}

inline void print(int x) {int a[25];a[0]=0;while(x) {a[++a[0]]=x&1;x>>=1;}while(a[0]) {printf("%d",a[a[0]--]);}printf(" ");}
inline void dijistra(int S) {
	while(Q.size()) {
		int x=Q.top().second;Q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(register int i=h[x];i;i=ver[i]) {
			int y=to[i];
			if(f[y][S]>f[x][S]+a[y]) Q.push(std::make_pair(-(f[y][S]=f[x][S]+a[y]),y)),pre[y][S]=x;
		}
	}
}
//inline void dijistra(int s){
//	while(Q.size()){
//		int x = Q.top().second;
//		Q.pop();
//		if(vis[x]) continue;
//		vis[x] = true;
//		for(int i=h[x]; i; i=ver[i]){
//			int y = to[i];
//			if(f[y][s] > f[x][s] + a[y]){
//				Q.push(std::make_pair(-(f[y][s] = f[x][s] + a[y]), y));
//				pre[y][s] = x;
//			}
//		}
//	}
//}
void dfs(int x,int S) {
	if(b[x][S]) return;
	b[x][S]=1;
	mp[x]=1;
	if(pre[x][S]!=-1&&f[pre[x][S]][S]+a[x]==f[x][S]) {
		int tmp=pre[x][S];
		while(tmp!=-1) {dfs(tmp,S);tmp=pre[tmp][S];}
	}
	for(register int S0=S;S0>=0;--S0) {
		if((S0|S)!=S) continue;
		if(f[x][S]==f[x][S0]+f[x][S-S0]-a[x]) {dfs(x,S0);dfs(x,S^S0);break;}
	}
}

//inline void dfs(int x, int s){
//	if(b[x][s]) return;
//	b[x][s] = true;
//	mp[x] = true;
//	if(pre[x][s] != 1 && f[pre[x][s]][s] + a[x] == f[x][s]){
//		int tmp = pre[x][s];
//		while(tmp != -1){
//			dfs(tmp, s);
//			tmp = pre[tmp][s];
//		}
//	}
//	for(int s1=s; s1>=0; s1--) {
//		if((s1 | s) != s) continue;
//		if(f[x][s] == f[x][s1] + f[x][s-s1] - a[x]){
//			dfs(x,s1);
//			dfs(x,s^s1);
//			break;
//		}
//	}
//}
int main() {
	int n=read(),m=read(),k=0,pos=-1;
	memset(f,0x3f,sizeof(f));
	memset(pre,-1,sizeof(pre));
//	for(register int i=0;i<n;++i) {
//		for(register int j=0;j<m;++j) {
//			if(!(a[id(i,j)]=read())) f[id(i,j)][1<<((++k)-1)]=0,pos=id(i,j);
//			if(i-1>=0) {
//				add(id(i-1,j),id(i,j));
//				add(id(i,j),id(i-1,j));
//			}
//			if(j-1>=0) {
//				add(id(i,j-1),id(i,j));
//				add(id(i,j),id(i,j-1));
//			}
//		}
//	}
	for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				a[id(i,j)] = read();
				if(!a[id(i,j)]){
					f[id(i,j)][1<<((++k)-1)] = 0;
					pos = id(i,j);
				}
				if(i-1 >= 0){
					add(id(i-1,j),id(i,j));
					add(id(i,j),id(i-1,j));
				}
				if(j-1>=0){
					add(id(i,j-1),id(i,j));
					add(id(i,j),id(i,j-1));
				}
			}
		}
//	for(register int S=1;S<(1<<k);++S) {
//		for(register int i=0;i<n*m;++i) {
//			for(register int S0=S;S0>=0;--S0) {
//				if((S0|S)!=S) continue;
//				f[i][S]=min(f[i][S],f[i][S0]+f[i][S-S0]-a[i]);//+a[i]*2 -> must -a[i]
//			}
//			vis[i]=0;
//			if(f[i][S]!=inf) Q.push(std::make_pair(-f[i][S],i));
//		}
//		dijistra(S);
//	}
	for(int s=1;s<(1<<k);s++) {
			for(int i=0;i<n*m;i++) {
				for(int s0=s;s0>=0;s0--) {
					if((s0 | s) != s) continue;
					f[i][s]=min(f[i][s], f[i][s0] + f[i][s-s0] - a[i]);	
				}
				vis[i] = false;
				if(f[i][s] != 0x3f3f3f3f) Q.push(std::make_pair(-f[i][s],i));
			}
			dijistra(s);
		}

//	if(pos!=-1) printf("%d\n",f[pos][(1<<k)-1]);
//	else printf("0\n");
//	dfs(pos,(1<<k)-1);
//	for(register int i=0;i<n;++i) {
//		for(register int j=0;j<m;++j) {
//			int x=id(i,j);
//			if(a[x]&&mp[x]) printf("o");
//			if(a[x]&&(!mp[x])) printf("_");
//			if(!a[x]) printf("x");
//		}
//		if(i!=n-1) printf("\n");
//	} 
	
	if(pos != -1)
			printf("%d\n",f[pos][(1<<k)-1]);
		else printf("0\n");
		dfs(pos,(1<<k)-1);
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				int x = id(i,j);
				if(a[x] && mp[x]) printf("o");
				if(a[x] && (!mp[x])) printf("_");
				if(!a[x]) printf("x");
			}
			if(i != n) printf("\n");
		} 
		
		
//	for(register int i=0;i<n*m;++i)
//		printf("%d ",a[i]);
//	for(register int S=1;S<(1<<k);++S){
//		for(register int i=0;i<n*m;++i){
//			printf("%d ", f[i][S]);
//		}
//		printf("\n");
//	}
	return 0;
}