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
#include<unordered_set>
#define MAXN 100010
#define MOD 1000000007
#define HMOD 9223372036854775783ULL
typedef unsigned long long ulnt;
ulnt pw[MAXN];
int n, d[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
inline void $(int u, int v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
	d[u]++; d[v]++;
}
int ans, id[MAXN], vis[MAXN];
ulnt hc0, hc1;
inline void up(int &x, int y){
	if((x += y) >= MOD)x -= MOD;
}
inline void hup(ulnt &x, ulnt y){if((x += y) >= HMOD) x -= HMOD;}
inline void hdown(ulnt &x, ulnt y){hup(x, HMOD - y);}
std::unordered_set<ulnt> s;
inline void gao(int x){
	for(int i = head[x];~i;i = next[i]) hup(hc0, pw[to[i]]), hdown(hc1, pw[to[i]]);
	s.insert(hc0); s.insert(hc1);
	for(int i = head[x];~i;i = next[i]) hdown(hc0, pw[to[i]]), hup(hc1, pw[to[i]]);
}
inline void cao(int x, int y){
	for(int i = 1;i <= n;i++)vis[i] = 0;
	for(int i = head[x];~i;i = next[i])vis[to[i]]++;
	for(int i = head[y];~i;i = next[i])vis[to[i]]++;
	for(int i = 1;i <= n;i++)if(vis[i] != (i != x && i != y))return;
	hup(hc0, pw[x]), hdown(hc1, pw[x]);
	for(int i = head[y];~i;i = next[i])hup(hc0, pw[to[i]]), hdown(hc1, pw[to[i]]);
	s.insert(hc0); s.insert(hc1);
	hdown(hc0, pw[x]), hup(hc1, pw[x]);
	for(int i = head[y];~i;i = next[i])hdown(hc0, pw[to[i]]), hup(hc1, pw[to[i]]);
}
inline int cmp(int x, int y){return d[x] < d[y];}
int main(){
	IOX io = IOX(/* fopen("C.in", "r")/* , fopen("C.out", "w") */);
	pw[1] = 1;
	for(int i = 2;i < MAXN;i++)pw[i] = (pw[i - 1] << 1) % HMOD;
	for(int T = io.getint();T;T--){
		n = io.getint();
		if(n == 1){io.putint(2);io.putchar(10);continue;}
		hc0 = hc1 = 0; tot = 0; s.clear(); ans = 1;
		for(int i = 1;i <= n;i++){hup(hc1, pw[i]);head[i] = -1;d[i] = 0;}
		for(int i = 1;i < n;i++)$(io.getint(), io.getint());
		for(int i = 1;i <= n;i++)up(ans, ans), gao(id[i] = i);
		std::sort(id + 1, id + n + 1, cmp);
		for(int i = n;i >= 1;i--){
			for(int j = i - 1;j >= 1;j--){
				if(d[id[i]] + d[id[j]] < n - 2)break;
				if(d[id[i]] + d[id[j]] == n - 2)cao(id[i], id[j]);
			}
		}
		up(ans, MOD - s.size());	
		io.putint(ans);
		io.putchar(10);
	}
	return 0;
}
