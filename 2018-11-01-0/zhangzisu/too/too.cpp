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
	inline int getalpha(){
		register char ch = getchar();
		while(!isalpha(ch))ch = getchar();
		return islower(ch) ? ch - 'a' + 26 : ch - 'A';
	}
};
#define MAXN 1010
#define MAXM 123
#define MOD 12345
typedef long long lnt;
lnt n;
int m, q = 1, t[MAXN], v[MAXN];
inline void up(int &x, int y){
	if((x += y) >= MOD) x -= MOD;
}
typedef int matrix[MAXM][MAXM];
typedef int vector[MAXM];
inline void mul(matrix &a, matrix &b, matrix &c){
	for(int i = 0;i < q;i++){
		for(int j = 0;j < q;j++){
			c[i][j] = 0;
		}
	}
	for(int k = 0;k < q;k++){
		for(int i = 0;i < q;i++){
			if(!a[i][k])continue;
			for(int j = 0;j < q;j++){
				if(!b[k][j])continue;
				up(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
			}
		}
	}
}
inline void mul(vector &a, matrix &b, vector &c){
	for(int i = 0;i < q;i++) c[i] = 0;
	for(int k = 0;k < q;k++){
		if(!a[k])continue;
		for(int j = 0;j < q;j++){
			if(!b[k][j])continue;
			up(c[j], 1LL * a[k] * b[k][j] % MOD);
		}
	}
}
int good[MAXN], val[MAXN], vis[52], ok[52];
void getMatrix(matrix &c){
	for(int i = 0;i < q;i++){
		for(int j = 0;j < q;j++){
			c[i][j] = 0;
		}
	}
	for(int now = 0;now < q;now++){
		memset(ok, 0, sizeof(ok));
		for(int x = now, j = 1;j <= m;j++){
			val[j] = x % v[j];
			x /= v[j];
			ok[t[j]] |= !val[j];
		}
		good[now] = 1;
		for(int x = 0;x < 52;x++){
			if(!vis[x])continue;
			good[now] &= ok[x];
			int next = 0;
			for(int j = 1;j <= m;j++){
				if(t[j] != x)continue;
				val[j] = (val[j] + 1) % v[j];
			}
			for(int j = m;j >= 1;j--){
				next = next * v[j] + val[j];
			}
			for(int j = 1;j <= m;j++){
				if(t[j] != x)continue;
				val[j] = (val[j] + v[j] - 1) % v[j];
			}
			up(c[now][next], 1);
		}
	}
}
matrix tr, tmp, re;
vector init, ans;
int ret = 0;
int main(){
	IOX io = IOX(fopen("too.in", "r"), fopen("too.out", "w"));
	n = io.getint64(); m = io.getint();
	for(int i = 1;i <= m;i++){
		t[i] = io.getalpha(); v[i] = io.getint();
		q *= v[i];
		vis[t[i]] = 1;
	}
//	fprintf(stderr, "q: %d\n", q);
	getMatrix(tr);
	for(int i = 0;i < q;i++){
		for(int j = 0;j < q;j++){
			re[i][j] = i == j;
		}
	}
	for(;n;n >>= 1){
		if(n & 1) {
			mul(re, tr, tmp);
			memcpy(re, tmp, sizeof(tmp));
		}
		mul(tr, tr, tmp);
		memcpy(tr, tmp, sizeof(tmp));
	}
//	for(int i = 0;i < q;i++){
//		for(int j = 0;j < q;j++){
//			printf("%d ", re[i][j]);
//		}
//		puts("");
//	}
	init[0] = 1;
	mul(init, re, ans);
	for(int i = 0;i < q;i++){
//		fprintf(stderr, "%d ", ans[i]);
		if(good[i]) up(ret, ans[i]);
	}
//	fprintf(stderr, "| %d\n", ret);
	io.putint(ret); io.putchar(10);
	return 0;
}
