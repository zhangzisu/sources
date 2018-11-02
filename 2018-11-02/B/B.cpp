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
			ocur = obuf;
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
		static int s[64];
		int t = 0;
		for(;x;x /= 10)s[++t] = x % 10;
		for(;t;t--)putchar(s[t] ^ 48);
	}
};
#include<vector>
#define MAXN 500010
#define DEEP 3000
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
lnt ans[MAXN];
std::vector<int> f[MAXN];
int now[DEEP], tmp[DEEP][DEEP];
void dp(int x, int d){
	for(int i = 1;i < deep[x];i++) ans[x] += 1LL * now[i - 1] * f[x][i];
	int *nbak = tmp[d];
	for(int i = head[x];~i;i = next[i]){
		if(to[i] == fa[x])continue;
		memcpy(nbak, now, sizeof(now));
		for(int j = deep[x] - 1;j;j--)now[j] = now[j - 1];
		now[0] = 0;
		for(int j = 0;j < deep[x];j++)now[j] += f[x][j] - ((j && j <= deep[to[i]]) ?  f[to[i]][j - 1] : 0);
		dp(to[i], d + 1);
		memcpy(now, nbak, sizeof(now));
	}
}
int main(){
	IOX io = IOX(fopen("B.in", "r"), fopen("B.out", "w"));
	n = io.getint();
	memset(head, -1, sizeof(head));
	for(int i = 1;i < n;i++)$(io.getint(), io.getint());
	dfs(1);
//	fprintf(stderr, "PASS %d\n", __LINE__);
	for(int _ = n;_ >= 1;_--){
		int x = pos[_];
		f[x].resize(deep[x]);
		f[x][0] = ans[x] = 1;
		for(int i = 1;i < deep[x];i++)f[x][i] = 0;
		for(int i = head[x];~i;i = next[i]){
			if(to[i] == fa[x])continue;
			for(int j = 0;j < deep[to[i]];j++) {
				ans[x] += 1LL * f[x][j + 1] * f[to[i]][j];
				f[x][j + 1] += f[to[i]][j];
			}
		}
	}
//	fprintf(stderr, "PASS %d\n", __LINE__);
	dp(1, 0);
//	fprintf(stderr, "PASS %d\n", __LINE__);
//	for(int i = 1;i <= n;i++)printf("%lld ", ans[i]);
//	puts("");
	for(int i = 1;i <= n;i++)io.putint64(ans[i]), io.putchar(i == n ? 10 : 32);
//	fprintf(stderr, "PASS %d\n", __LINE__);
	return 0;
}
