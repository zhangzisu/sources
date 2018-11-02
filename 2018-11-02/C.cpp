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
		static int s[32];
		int t = 0;
		for(;x;x /= 10)s[++t] = x % 10;
		for(;t;t--)putchar(s[t] ^ 48);
	}
};
#define MAXN 10
int n; //, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
//inline void $(int u, int v){
//	next[tot] = head[u], to[tot] = v, head[u] = tot++;
//	next[tot] = head[v], to[tot] = u, head[v] = tot++;
//}
int p[MAXN], g[MAXN][MAXN];
inline int find(int x){return x == p[x] ? x : p[x] = find(p[x]); }
int main(){
	IOX io = IOX(fopen("C.in", "r"), fopen("C.out", "w"));
	for(int T = io.getint();T;T--){
		n = io.getint();
//		memset(head, -1, sizeof(head));
//		tot = 0;
		memset(g, 0, sizeof(g));
		for(int i = 1;i < n;i++) {
			int u = io.getint() - 1, v = io.getint() - 1;
			g[u][v] = g[v][u] = 1;
		}
		int ans = 0;
		for(int i = 0;i < (1 << n);i++){
			for(int j = 0;j < n;j++)p[j] = j;
			for(int j = 0;j < n;j++){
				for(int k = 0;k < n;k++){
					if(((i >> j) & 1) ^ ((i >> k) & 1) ^ g[j][k]){
						p[find(j)] = find(k);
					}
				}
			}
			int tmp = 0;
			for(int j = 0;j < n;j++)tmp += find(j) == j;
			ans += tmp == 1;
		}
		io.putint(ans);
		io.putchar(10);
	}
	return 0;
}
