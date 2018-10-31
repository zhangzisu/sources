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
#define MAXN 300010
typedef long long lnt;
struct sbx {
    int x0, y0, x1, y1;
    inline sbx friend operator&(sbx a, sbx b) {
        sbx c;
        c.x0 = std::max(a.x0, b.x0);
        c.y0 = std::max(a.y0, b.y0);
        c.x1 = std::min(a.x1, b.x1);
        c.y1 = std::min(a.y1, b.y1);
        return c;
    }
} pre[MAXN], suf[MAXN], val[MAXN];
int T, p, q, n;
int main() {
    IOX io = IOX(fopen("carpet.in", "r"), fopen("carpet.out", "w"));
    for (T = io.getint(); T; T--) {
        p = io.getint(), q = io.getint(), n = io.getint();
        for (int i = 1; i <= n; i++) {
            val[i].x0 = io.getint();
            val[i].y0 = io.getint();
            val[i].x1 = io.getint();
            val[i].y1 = io.getint();
        }
        pre[0] = suf[n + 1] = (sbx){0, 0, p, q};
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] & val[i];
        for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] & val[i];
        lnt ans = 0;
        for (int i = 1; i <= n; i++) {
            sbx tmp = pre[i - 1] & suf[i + 1];
            if (tmp.x0 < tmp.x1 && tmp.y0 < tmp.y1) ans += 1LL * (tmp.x1 - tmp.x0) * (tmp.y1 - tmp.y0);
        }
        sbx all = pre[n];
        if (all.x0 < all.x1 && all.y0 < all.y1) ans -= 1LL * (n - 1) * (all.x1 - all.x0) * (all.y1 - all.y0);
        io.putint64(ans);
        io.putchar(10);
    }
}