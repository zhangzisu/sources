#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
class IO{
  protected:
	const static int BUF = 65536;
	FILE *in, *out;
	char ibuf[BUF], obuf[BUF], *icur, *ocur;
	int ilimit;
  public:
	inline IO(FILE *in = stdin, FILE *out = stdout){
		this->in = in;
		this->out = out;
		this->icur = this->ibuf + BUF;
		this->ocur = this->obuf;
	}
	inline int getchar(){
		if(icur == ibuf + BUF){
			ilimit = fread(ibuf, 1, BUF, in);
			icur = ibuf;
		}
		return (icur < ibuf + ilimit) ? *icur++ : -1;
	}
	inline void putchar(char c){
		if(ocur == obuf + BUF){
			fwrite(obuf, 1, BUF, out);
		}
		*ocur++ = c;
	}
	inline ~IO(){
		fwrite(obuf, 1, ocur - obuf, out);
	}
};
class IOX : public IO{
  public:
  	inline IOX(FILE *in = stdin, FILE *out = stdout): IO(in, out){}
	inline int getint(){
		register int x = 0;
		register char ch = getchar();
		while(!isdigit(ch))ch = getchar();
		for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline void putint(int x){
		if(x == 0)return putchar(48);
		if(x < 0)putchar(45), x = -x;
		static int s[32];
		int t = 0;
		for(;x;x /= 10)s[++t] = x % 10;
		for(;t;t--)putchar(s[t] ^ 48);
	}
};
#define MAXN 200010
#define MAXM 400010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int dfn[MAXN], low[MAXN], ins[MAXN], stk[MAXN], bel[MAXN], snt = 0, top = 0, dfsclk = 0;
int a[MAXN], s[MAXN];
void dfs(int x, int fa){
	dfn[x] = low[x] = ++dfsclk;
	ins[stk[++top] = x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(i == fa)continue;
		if(dfn[to[i]]){
			if(!ins[to[i]])continue;
			low[x] = std::min(low[x], dfn[to[i]]);
		}else{
			dfs(to[i], i ^ 1);
			low[x] = std::min(low[x], low[to[i]]);
		}
	}
	if(low[x] == dfn[x]){
		++snt;
		do{
			ins[stk[top]] = 0;
			bel[stk[top]] = snt;
			s[snt] += a[stk[top]];
		}while(stk[top--] != x);
	}
}
int n, m, u[MAXM], v[MAXM], f[MAXN], ans = 0;
void dp(int x, int fa){
	int max0 = 0, max1 = 0;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa)continue;
		dp(to[i], x);
		if(f[to[i]] >= max0)max1 = max0, max0 = f[to[i]];
		else if(f[to[i]] >= max1)max1 = f[to[i]];
	}
	ans = std::max(ans, max0 + max1 + s[x]);
	f[x] = max0 + s[x];
}
int main(){
	IOX io = IOX(fopen("robber.in", "r"), fopen("robber.out", "w"));
	n = io.getint(); m = io.getint();
	for(int i = 1;i <= n;i++)a[i] = io.getint();
	memset(head, -1, sizeof(head)); tot = 0;
	for(int i = 1;i <= m;i++){
		u[i] = io.getint(); 
		v[i] = io.getint();
		$(u[i], v[i]);
	}
	dfs(1, -1);
	memset(head, -1, sizeof(head)); tot = 0;
	for(int i = 1;i <= m;i++){
		u[i] = bel[u[i]];
		v[i] = bel[v[i]];
		if(u[i] != v[i])$(u[i], v[i]);
	}
	dp(1, 0);
	io.putint(ans);
	io.putchar(10);
	return 0;
}
