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
#include<queue>
#define MOD 1000000007
#define MAXN 510
#define MAXM 100010
inline void up(int &x, int y){
	if((x += y) >= MOD)x -= MOD;
}
int n, m, k, in[MAXN], out[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v){
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
std::queue<int> Q;
int id[MAXN], sc, tc;
inline void swap(int x, int y){
	for(int i = 1;i <= k;i++)std::swap(g[x][i], g[y][i]);
}
inline int fuck(int x, int p){
	int y = 1;
	for(;p;p >>= 1){
		if(p & 1)y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int main(){
	IOX io = IOX(/* fopen("network.in", "r"), fopen("network.out", "w") */);
	memset(head, -1, sizeof(head));
	n = io.getint(), m = io.getint(), k = io.getint();
	for(int i = 1;i <= m;i++){
		int u = io.getint(), v = io.getint();
		$(u, v); out[u]++; in[v]++;
	}
	for(int i = 1;i <= n;i++){
		if(!in[i])id[i] = ++sc;
		if(!out[i])id[i] = ++tc;
	}
	for(int i = 1;i <= n;i++){
		if(!in[i]){
			f[i][id[i]] = 1;
			Q.push(i);
		}
	}
	while(Q.size()){
		int x = Q.front();
		Q.pop();
		for(int i = head[x];~i;i = next[i]){
			for(int j = 1;j <= k;j++) up(f[to[i]][j], f[x][j]);
			if(!--in[to[i]])Q.push(to[i]);
		}
	}
	for(int i = 1;i <= n;i++){
		if(!out[i]){
			for(int j = 1;j <= k;j++)g[j][id[i]] = f[i][j];
		}
	}
//	for(int i = 1;i <= k;i++){
//		for(int j = 1;j <= k;j++){
//			printf("g[%d][%d] = %d\n", i, j, g[i][j]);
//		}
//	}
	int t = 0;
	for(int i = 1;i <= k;i++){
		int p = 0;
		for(int j = i;j <= k;j++){
			if(g[j][i]){
				p = j;
				break;
			}
		}
		if(!p) return io.putint(0), io.putchar(10), 0;
		if(i != p) swap(i, p), t++;
		for(int j = i + 1, inv = fuck(g[i][i], MOD - 2);j <= k;j++){
			if(!g[j][i])continue;
			int delta = 1LL * g[j][i] * inv % MOD;
			for(int l = i;l <= k;l++) up(g[j][l], MOD - 1LL * g[i][l] * delta % MOD);
		}
	}
	int ans = 1;
	for(int i = 1;i <= k;i++)ans = 1LL * ans * g[i][i] % MOD;
	if(t & 1)ans = MOD - ans;
	io.putint(ans);
	io.putchar(10);
	return 0;
}
