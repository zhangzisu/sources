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
		register bool f = 0;
		for(;!isdigit(ch);ch = getchar())f ^= (ch == 45);
		for(;isdigit(ch);ch = getchar())x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
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
#define MAXN 2000010
typedef long long lnt;
int T, n;
int main(){
	IOX io = IOX(fopen("stone.in", "r"), fopen("stone.out", "w"));
	for(T = io.getint();T;T--){
		n = io.getint();
		if(n == 1){
			io.putint(io.getint());
			continue;
		}
		lnt sum = 0;
		bool ls = 0, eq = 0, gt = 0;
		int min = (~0U) >> 1;
		for(int i = 1;i <= n;i++){
			int x = io.getint();
			sum += std::abs(x);
			ls |= x < 0;
			eq |= x == 0;
			gt |= x > 0;
			min = std::min(min, std::abs(x));
		}
		if(eq || (ls && gt))io.putint64(sum);
		else io.putint64(sum - min * 2);
		io.putchar(10);
	}
	return 0;
}
