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
#include <queue>
#define MAXN 1000010
int n, m, next[MAXN], a[MAXN], pos[2010];
std::priority_queue<int> P, Q;
inline void add(int x) { P.push(x); }
inline void del(int x) { Q.push(x); }
inline int top() {
    while (Q.size() && P.top() == Q.top()) P.pop(), Q.pop();
    return P.top();
}
int u, v = MAXN;
int main() {
    IOX io = IOX(fopen("Exhibit.in", "r"), fopen("Exhibit.out", "w"));
    n = io.getint(), m = io.getint();
    for (int i = 1; i <= n; i++) a[i] = io.getint();
    for (int i = 1; i <= m; i++) pos[i] = n + 1;
    for (int i = n; i >= 1; i--) {
        next[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= m; i++) add(pos[i]);
    for (int i = 1; i <= n; i++) {
        int j = top();
        if (j > n) break;
        if (j - i < v - u) u = i, v = j;
        del(i);
        add(next[i]);
    }
    io.putint(u), io.putchar(32), io.putint(v), io.putchar(10);
    return 0;
}