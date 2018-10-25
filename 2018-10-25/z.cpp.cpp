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
#include <queue>
#define MAXN 100010
typedef long long lnt;
int n, q, x[MAXN], y[MAXN], ans[MAXN], id[MAXN];
inline int cmp(int a, int b) { return y[a] < y[b]; }
int pre[MAXN], next[MAXN];
lnt sum = 0;
std::priority_queue<std::pair<int, int>> Q, P;
inline void add(int len, int pos) {
    Q.emplace(-len, pos);
    sum += len;
}
inline void del(int len, int pos) {
    P.emplace(-len, pos);
    sum -= len;
}
inline std::pair<int, int> top() {
    while (Q.size() && P.size() && Q.top() == P.top()) Q.pop(), P.pop();
    return Q.top();
}
inline void pop() { Q.pop(); }
inline int size() { return Q.size() - P.size(); }
int main() {
    IOX io = IOX();
    n = io.getint();
    q = io.getint();
    for (int i = 1; i <= n; i++) x[i] = io.getint();
    for (int i = 1; i <= n; i++) pre[i] = i - 1;
    for (int i = 1; i <= n; i++) next[i] = i + 1;
    pre[n + 1] = n, next[0] = 1;
    for (int i = 1; i <= q; i++) y[i] = io.getint();
    for (int i = 1; i <= q; i++) id[i] = i;
    for (int i = 1; i <= n; i = next[i]) {
        if (next[i] > n) break;
        while (true) {
            int j = next[i], k = next[j];
            if (k > n) break;
            if ((x[i] <= x[j] && x[j] <= x[k]) || (x[i] >= x[j] && x[j] >= x[k])) {
                next[i] = next[j];
                pre[k] = pre[j];
            } else {
                break;
            }
        }
        add(std::abs(x[next[i]] - x[i]), i);
    }
    for (int d = 1; d <= q; d++) {
        int &len = ::y[id[d]];
        int &ans = ::ans[id[d]];
        for (int i = next[0]; i <= n && x[i] >= 0 && x[i] <= len; i = next[0]) {
            del(std::abs(x[next[i]] - x[i]), i);
            next[pre[i]] = next[i];
            pre[next[i]] = pre[i];
        }
        if (!size()) {
            ans = 0;
        } else if (size() == 1) {
            ans = std::min(std::abs(x[next[0]]), std::abs(x[next[0]] - len));
        } else {
            if (x[next[0]] < 0) {
                if (x[next[next[0]]] < x[next[0]]) {
                    ans = len - x[next[0]];
                } else {
                    ans = -x[next[0]];
                }
            } else {
                if (x[next[next[0]]] < x[next[0]]) {
                    ans = x[next[0]] - len;
                } else {
                    ans = x[next[0]];
                }
            }
            while (size()) {
                auto t = top();
                if (-t.first > len) break;
                int p = t.second, l, r;
                if (x[next[p]] > x[p]) {
                    l = x[p], r = l + len;
                } else {
                    r = x[p], l = r - len;
                }
                for (int i = next[p]; i <= n && x[i] >= l && x[i] <= r; i = next[p]) {
                    del(std::abs(x[i] - x[p]), p);
                    del(std::abs(x[next[i]] - x[i]), i);
                    next[pre[i]] = next[i];
                    pre[next[i]] = pre[i];
                    if (next[i] <= n) add(std::abs(x[next[i]] - x[p]), p);
                }
            }
            ans += sum - size() * len;
        }
    }
    for (int i = 1; i <= q; i++) io.putint(ans[i]), io.putchar(10);
    return 0;
}