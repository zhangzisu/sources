#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
   protected:
    const static int BUF = 65536;
    FILE *in, *out;
    char ibuf[BUF], obuf[BUF], *icur, *ocur;
    int ilimit;

   public:
    inline IO(FILE *in = stdin, FILE *out = stdout) {
        this->in = in;
        this->out = out;
        this->icur = this->ibuf + BUF;
        this->ocur = this->obuf;
    }
    inline int getchar() {
        if (icur == ibuf + BUF) {
            ilimit = fread(ibuf, 1, BUF, in);
            icur = ibuf;
        }
        return (icur < ibuf + ilimit) ? *icur++ : -1;
    }
    inline void putchar(char c) {
        if (ocur == obuf + BUF) {
            fwrite(obuf, 1, BUF, out);
            ocur = obuf;
        }
        *ocur++ = c;
    }
    inline ~IO() {
        fwrite(obuf, 1, ocur - obuf, out);
    }
};
class IOX : public IO {
   public:
    inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
    inline int getint() {
        register int x = 0;
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        register long long x = 0;
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline char getAlpha() {
        register char ch = getchar();
        while (!isalpha(ch)) ch = getchar();
        return ch;
    }
    inline void putint(int x) {
        if (x == 0) return putchar(48);
        if (x < 0) putchar(45), x = -x;
        static int s[32];
        int t = 0;
        for (; x; x /= 10) s[++t] = x % 10;
        for (; t; t--) putchar(s[t] ^ 48);
    }
    inline void putint64(long long x) {
        if (x == 0) return putchar(48);
        if (x < 0) putchar(45), x = -x;
        static int s[32];
        int t = 0;
        for (; x; x /= 10) s[++t] = x % 10;
        for (; t; t--) putchar(s[t] ^ 48);
    }
};
inline int lowbit(int x) { return x & -x; };
int calc(int l, int r) {
    int cnt = 0;
    while (l <= r) {
        int x = lowbit(r);
        cnt = cnt + 1;
        if (r - x + 1 >= l)
            r = r - x;
        else
            r = r - 1;
    }
    return cnt;
}
int n, ans;
int main() {
    IOX io(fopen("fenwick.in", "r"), fopen("fenwick.out", "w"));
    n = io.getint();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ans += calc(i, j);
        }
    }
    io.putint(ans);
    return 0;
}