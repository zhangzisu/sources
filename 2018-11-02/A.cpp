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
};
#define MAXN 2000000
typedef long long lnt;
int T;
lnt a, l, r;
int vis[MAXN], pri[MAXN], pnt = 0;
inline void shai(){
	for(int i = 2;i < MAXN;i++){
		if(!vis[i])pri[++pnt] = i;
		for(int j = 1;j <= pnt;j++){
			if(1LL * i * pri[j] >= MAXN)break;
			vis[i * pri[j]] = 1;
			if(i % pri[j] == 0)break;
		}
	}
}
int main(){
	shai();
	IOX io = IOX(/* fopen("A.in", "r"), fopen("A.out", "w") */);
	for(T = io.getint();T;T--){
		l = io.getint(); r = io.getint(); a = io.getint();
		if(a > r){
			io.putint(-1);
			io.putchar(10);
		}else{
			int ans = 1;
			for(int i = 1;a != 1 && i <= pnt && pri[i] <= a;i++){
				if(a % pri[i])continue;
				int cnt = 0;
				while(a % pri[i] == 0)a /= pri[i], cnt++;
				ans *= cnt;
			}
			io.putint(ans);
			io.putchar(10);
		}
	}
	return 0;
}
