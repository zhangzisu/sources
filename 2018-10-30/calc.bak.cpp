#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
   protected:
    static const int BSIZE = 65536;
    int is;
    char ib[BSIZE], ob[BSIZE], *ip, *op;
    FILE *in, *out;

   public:
    inline IO(FILE *in = stdin, FILE *out = stdout) {
        ip = ib + BSIZE, op = ob, is = 0;
        this->in = in;
        this->out = out;
    }
    inline ~IO() {
        fwrite(ob, 1, op - ob, out);
    }
    inline char getchar() {
        if (ip == ib + BSIZE) is = fread(ib, 1, BSIZE, in), ip = ib;
        return ip == ib + is ? 0 : *ip++;
    }
    inline void putchar(char c) {
        if (op == ob + BSIZE) fwrite(ob, 1, BSIZE, out), op = ob;
        *op++ = c;
    }
};
class IOX : public IO {
   protected:
    int tmp[64];

   public:
    inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
    inline int getdigit() {
        char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline int getint() {
        int x = 0, f = 0;
        char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        unsigned x = 0;
        char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
#include <vector>
#define MAXN 10000010
#define MAXM 1010
#define MOD 1000000007
#define INV 500000004
inline int fuck(int x, int p){
    int y = 1;
    for(;p;p>>=1){
        if(p&1)y=1LL*y*x%MOD;
        x=1LL*x*x%MOD;
    }
    return y;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, m, a[MAXM], b[MAXN], ans;
int main() {
    IOX io = IOX();
    n = io.getint(), m = io.getint();
    for (int i = 1, s = 0; i <= m; i++) {
        a[i] = io.getint();
        b[i] = a[i] - a[i - 1];
        s += a[i];
    }
    for(int i = m;i >= 1;i--){
        int stat = 1;
        for(int j=i+1;j<=m;j++){
            //
        }
    }
    io.putint(ans);
    io.putchar(10);
    for (int i = 1; i <= n; i++) fprintf(stderr, "%d ", v[i]);
    fprintf(stderr, "\n");
    return 0;
}