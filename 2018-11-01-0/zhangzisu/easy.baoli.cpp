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
#define MOD 991127
#define MAXN 200010
#define LOGV 31
int n, a[MAXN], f[MAXN];
inline void up(int &x, int y){
	if((x += y) >= MOD)x -= MOD;
}
int main(){
	IOX io = IOX(fopen("easy.in", "r"), fopen("easy.out", "w"));
	n = io.getint();
	for(int i = 1;i <= n;i++) a[i] = io.getint();
	f[1] = 1;
	for(int i = 2;i <= n;i++){
		for(int j = 1;j < i;j++) up(f[i], 1LL * f[j] * __builtin_popcount(a[i] & a[j]) % MOD);
	}
	io.putint(f[n]);
	return 0;
}
