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
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline int getint() {
        register int x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
#define MAXN 310
#define MAXT 120
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int n, k, t[MAXN], id[MAXT], f[MAXN][MAXT], ans;
inline int fuck0() {
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < t[i]; j++) tmp = std::max(tmp, f[i][j]);
        ans += tmp;
    }
    printf("%d\n", ans);
    return 0;
}
int main() {
    IOX io;
    n = io.getint();
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; i++) {
        t[i] = io.getint();
        if (id[t[i]] != -1) {
            for (int j = 0; j < t[i]; j++) {
                f[id[t[i]]][j] += io.getint();
            }
            n--, i--;
        } else {
            for (int j = 0; j < t[i]; j++) {
                f[i][j] = io.getint();
            }
            id[t[i]] = i;
            k = k ? k / gcd(k, t[i]) * t[i] : t[i];
        }
    }
    bool flag = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            flag &= gcd(t[i], t[j]) == 1;
        }
    }
    if (flag) return fuck0();
    for (int i = 0; i < k; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) tmp += f[j][i % t[j]];
        ans = std::max(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}