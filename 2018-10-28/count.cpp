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
#define MOD 1000000007
typedef long long lnt;
int n, c, d, p;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int a[10], b[10], v[10], V, size;
typedef int matrix[80][80];
typedef int vector[80];
inline void mul(matrix &a, matrix &b, matrix &c) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            c[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                up(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
}
inline void mul(vector &a, matrix &b, vector &c) {
    for (int i = 0; i < size; i++) {
        c[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            up(c[j], 1LL * a[i] * b[i][j] % MOD);
        }
    }
}
inline int getPos(int i, int j) {
    return i * (p + 1) + j;
}
inline void fuck(matrix &x, int p, matrix &y) {
    static matrix tmp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            y[i][j] = (i == j);
        }
    }
    for (; p; p >>= 1) {
        if (p & 1) {
            mul(y, x, tmp);
            memcpy(y, tmp, sizeof(tmp));
        }
        mul(x, x, tmp);
        memcpy(x, tmp, sizeof(tmp));
    }
}
inline void getMatrix(int a, matrix &b) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            b[i][j] = 0;
        }
    }
    for (int j = 0; j <= c; j++) {
        for (int k = 0; k <= p; k++) {
            int now = getPos(j, k);
            up(b[now][getPos(j, k)], 1);
            if (j && a != j) {
                up(b[now][getPos(0, k)], 1);
            }
            if (k == p) continue;
            for (int l = 1; l <= c; l++) {
                if (l == a || (j <= V && j == l)) continue;
                if (l <= V) {
                    up(b[now][getPos(l, k + 1)], 1);
                } else {
                    up(b[now][getPos(l, k + 1)], (d - V - (j > V)));
                }
            }
        }
    }
}
vector f, g;
matrix trans, trant;
int main() {
    IOX io = IOX();
    V = n = io.getint(), d = c = io.getint(), p = io.getint();
    for (int i = 1; i <= n; i++) v[i] = a[i] = io.getint(), b[i] = io.getint();
    std::sort(v + 1, v + V + 1);
    V = std::unique(v + 1, v + V + 1) - v - 1;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + V + 1, a[i]) - v;
    c = std::min(c, V + 1);
    size = (c + 1) * (p + 1);
    f[getPos(0, 0)] = 1;
    for (int i = 1; i <= n; i++) {
        getMatrix(a[i], trans);
        fuck(trans, b[i], trant);
        mul(f, trant, g);
        memcpy(f, g, sizeof(g));
    }
    int ans = 0;
    for (int i = 0; i <= p; i++) {
        for (int j = 0; j <= c; j++) {
            up(ans, f[getPos(j, i)]);
        }
    }
    io.putint(ans);
    io.putchar(10);
    return 0;
}