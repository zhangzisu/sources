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
#define MAXN 1010
#include<set>
#include<cassert>
int n, m, k, t;
int x[MAXN], y[MAXN], d[MAXN], f[MAXN], del[MAXN], vis[MAXN][MAXN];
std::set<int> S;
int main(){
	IOX io = IOX(fopen("problem.in", "r"), fopen("problem.out", "w"));
	n = io.getint(); m = io.getint(); k = io.getint();
	for(int i = 1;i <= k;i++){
		x[i] = io.getint(); y[i] = io.getint(); d[i] = io.getint(); f[i] = io.getint();
		assert(!S.count(f[i]));
		S.insert(f[i]);
	}
	//
	for(int i = 1;i <= k;i++)io.putint(x[i]), io.putchar(32), io.putint(y[i]), io.putchar(10);
	return 0;
}
