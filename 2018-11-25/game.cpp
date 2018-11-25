#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
        putchar(10);
    }
};
int n, m, G[150][150];
inline int gauss() {
    for (int i = 0; i < n; i++) {
        int p = i;
        while (p < n && !G[p][i]) p++;
        if (p >= n) return 0;
        if (p != i) {
            for (int j = i; j < n; j++) std::swap(G[i][j], G[p][j]);
        }
        for (p = i + 1; p < n; p++) {
            if (!G[p][i]) continue;
            for (int j = i; j < n; j++) G[p][j] ^= G[i][j];
        }
    }
    return 1;
}
int main() {
    IOX io;
    for (int T = io.getint(); T; T--) {
        n = io.getint();
        m = io.getint();
        memset(G, 0, sizeof(G));
        for (int i = 0; i < m; i++) {
            int x = io.getint() - 1;
            int y = io.getint() - 1;
            G[x][y] ^= 1;
        }
        io.puts(gauss() ? "NO" : "YES");
    }
    return 0;
}