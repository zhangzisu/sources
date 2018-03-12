#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define MAXN 1200010
#define SIGMA 26

char buf[3000005], op[3000005];
int last = 1, cnt = 1;

inline void CCF(int mask){
	scanf("%s", buf);
	int len = strlen(buf);
	for(int i = 0;i < len;i++){
		mask = (mask * 131 + i) % len;
		std::swap(buf[i], buf[mask]);
	}
}
int mask = 0;
int w[MAXN], tag[MAXN];

class LCT{
  private:
	int L[MAXN], R[MAXN], F[MAXN];
	inline int Root(int x){return L[F[x]] != x && R[F[x]] != x;}
	inline void pushDown(int x){
		if(tag[x]){
			tag[L[x]] += tag[x]; w[L[x]] += tag[x];
			tag[R[x]] += tag[x]; w[R[x]] += tag[x];
			tag[x] = 0;
		}
	}
	inline void Left(int x){
		int y = F[x]; F[R[y] = L[x]] = y; F[x] = F[y];
		if(!Root(y)){
			if(y == L[F[y]])L[F[y]] = x;
			if(y == R[F[y]])R[F[y]] = x;
		}
		L[x] = y; F[y] = x;
	}
	inline void Right(int x){
		int y = F[x]; F[L[y] = R[x]] = y; F[x] = F[y];
		if(!Root(y)){
			if(y == L[F[y]])L[F[y]] = x;
			if(y == R[F[y]])R[F[y]] = x;
		}
		R[x] = y; F[y] = x;
	}
  public:	
	inline void Splay(int x){
		static int stack[MAXN], top = 0, y = x;
		for(y = x;!Root(y);y = F[y])stack[++top] = y;
		pushDown(y);
		while(top)pushDown(stack[top--]);
		while(!Root(x)){
			int y = F[x];
			if(Root(y)){
				if(L[y] == x)Right(x);else Left(x);
			}else{
				int z = F[y];
				if(L[z] == y){
					if(L[y] == x)Right(y), Right(x);
					else Left(x), Right(y);
				}else{
					if(R[z] == y && L[y] == x)Right(x), Left(y);
					else Left(y), Left(x);
				}
			}
		}
	}
	inline void Access(int x){
		for(int t = 0;x;t = x, x = F[x])Splay(x), R[x] = t;
	}
	inline LCT(){
		memset(L, 0, sizeof(L));
		memset(R, 0, sizeof(R));
		memset(F, 0, sizeof(F));
	}
	inline void Link(int x, int y){
		F[x] = y; Access(y); Splay(y);
		tag[y] += w[x]; w[y] += w[x];
	}
	inline void Cut(int x){
		Access(x); Splay(x); tag[L[x]] -= w[x]; w[L[x]] -= w[x];
		F[L[x]] = 0; L[x] = 0;
	}
	inline void print(int x, int deep = 0){
		if(!x)return;
		print(L[x], deep + 2);
		printf("SPLAY %3d |>>   ", x);
		for(int i = 1;i <= deep;i++)putchar(' ');
		printf("W : %3d, L : %3d, R : %3d, F = %3d\n", w[x], L[x], R[x], F[x]);
		print(R[x], deep + 4);
	}
}lct;

struct state{
	int son[SIGMA], link, len;
	inline state(int len = 0){
		this->len = len;this->link = 0;
		memset(son, 0, sizeof(son));
	}
	inline state(state &x, int len){
		this->len = len;this->link = x.link;
		memcpy(son, x.son, sizeof(son));
	}
	inline int &operator[] (int x){return son[x];}
}sam[MAXN];

inline void extend(int x){
	int pre = last, cur = ++cnt, son, cln;
	sam[cur] = state(sam[pre].len + 1); w[cur] = 1;
	last = cur;
	for(;pre && !sam[pre][x];pre = sam[pre].link)sam[pre][x] = cur;
	if(!pre)return lct.Link(cur, sam[cur].link = 1);
	son = sam[pre][x];
	if(sam[pre].len + 1 == sam[son].len)return lct.Link(cur, sam[cur].link = son);
	sam[cln = ++cnt] = state(sam[son], sam[pre].len + 1); lct.Link(cln, sam[cln].link);
	for(;pre && sam[pre][x] == son;pre = sam[pre].link)sam[pre][x] = cln;
	lct.Cut(son); lct.Link(cur, sam[cur].link = cln); lct.Link(son, sam[son].link = cln);
}

int main(){
	int q; scanf("%d", &q);
	scanf("%s", buf);
	for(int i = 0;buf[i];i++)extend(buf[i] - 'A');
	while(q--){
		scanf("%s", op);
		CCF(mask);
		if(op[0] == 'A'){
			for(register int i = 0;buf[i];i++)extend(buf[i] - 'A');
		}else{
			//for(int i = 1;i <= cnt;i++)printf("SAM [%3d] : len = %3d, link = %3d\n", i, sam[i].len, sam[i].link);
			register int p = 1;
			for(register int i = 0;buf[i];i++)if(!(p = sam[p][buf[i] - 'A']))goto fail;
			lct.Splay(p);
			//lct.print(p);
			printf("%d\n", mask = w[p]);
			continue;
			fail:puts("0");
		}
	}
	return 0;
}