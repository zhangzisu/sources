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
	inline long long getint64(){
		register long long x = 0;
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
	inline void putint64(long long x){
		if(x == 0)return putchar(48);
		if(x < 0)putchar(45), x = -x;
		static int s[32];
		int t = 0;
		for(;x;x /= 10)s[++t] = x % 10;
		for(;t;t--)putchar(s[t] ^ 48);
	}
};
#include<vector>
#define MAXN 100010
#define DEEP 1500
typedef long long lnt;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int dfn[MAXN], pos[MAXN], fa[MAXN], deep[MAXN], dfsclk;
void dfs(int x){
	pos[dfn[x] = ++dfsclk] = x;
	deep[x] = 1;
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa[x])continue;
		fa[to[i]] = x; dfs(to[i]); deep[x] = std::max(deep[x], deep[to[i]] + 1);
	}
}
int main(){
	IOX io = IOX(fopen("B.in", "r"));
	n = io.getint();
	memset(head, -1, sizeof(head));
	for(int i = 1;i < n;i++)$(io.getint(), io.getint());
	dfs(1);
	int sum = 0;
	for(int i = 1;i <= n;i++) sum += deep[i];
	io.putint(sum);
	io.putchar(10);
	return 0;
}
