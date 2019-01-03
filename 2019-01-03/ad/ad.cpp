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
    inline char getalpha() {
        register char ch = getchar();
        while (!isalpha(ch)) ch = getchar();
        return ch;
    }
    inline int getint() {
        register int x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned long long getuint64() {
        register unsigned long long x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return x;
    }
    inline void put(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void put(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void put(const char *s) {
        for (; *s; s++) putchar(*s);
    }
    inline void put(char c) { putchar(c); }
    template <typename T, typename... Args>
    inline void put(T first, Args... rest) { put(first), put(rest...); }
    inline void puts(const char *s) {
        put(s);
        putchar(10);
    }
} io(fopen("ad.in", "r"), fopen("ad.out", "w"));
#define MAXN 800010
const int INF = 0x3F3F3F3F;
int v[MAXN], vcnt;
inline int lowbit(int x) { return x & -x; }
namespace bit1 {
int max[MAXN];
inline void mdf(int x, int y) {
    for (; x <= vcnt; x += lowbit(x)) max[x] = std::max(max[x], y);
}
inline int qry(int x) {
    int y = 0;
    for (; x; x -= lowbit(x)) y = std::max(y, max[x]);
    return y;
}
}  // namespace bit1
namespace bit2 {
int min[MAXN];
inline void mdf(int x, int y) {
    for (; x; x -= lowbit(x)) min[x] = std::min(min[x], y);
}
inline int qry(int x) {
    int y = vcnt + 1;
    for (; x <= vcnt; x += lowbit(x)) y = std::min(y, min[x]);
    return y;
}
}  // namespace bit2
namespace zmt {
int max[MAXN * 20], ls[MAXN * 20], rs[MAXN * 20], root[MAXN], tot = 0;
inline int modify(int n, int l, int r, int p, int v) {
    int cur = ++tot;
    max[cur] = std::max(max[n], v), ls[cur] = ls[n], rs[cur] = rs[n];
    if (l != r) {
        int mid = (l + r) >> 1;
        if (p <= mid) {
            ls[cur] = modify(ls[cur], l, mid, p, v);
        } else {
            rs[cur] = modify(rs[cur], mid + 1, r, p, v);
        }
    }
    return cur;
}
inline int query(int n, int l, int r, int L, int R) {
    if (!n) return 0;
    if (l == L && r == R) return max[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls[n], l, mid, L, R);
    if (L > mid) return query(rs[n], mid + 1, r, L, R);
    return std::max(query(ls[n], l, mid, L, mid), query(rs[n], mid + 1, r, mid + 1, R));
}
}  // namespace zmt
int n = io.getint(), m = io.getint(), l[MAXN], r[MAXN], id[MAXN], a[MAXN], b[MAXN], c[MAXN];
long long ans = 0;
int main() {
    for (int i = 1; i <= n; i++) v[++vcnt] = l[i] = io.getint(), v[++vcnt] = r[i] = io.getint();
    for (int i = 1; i <= m; i++) v[++vcnt] = a[i] = io.getint(), v[++vcnt] = b[i] = io.getint(), c[i] = io.getint();
    std::sort(v + 1, v + vcnt + 1);
    vcnt = std::unique(v + 1, v + vcnt + 1) - v - 1;
    v[vcnt + 1] = INF;
    std::fill(bit2::min + 1, bit2::min + vcnt + 1, vcnt + 1);
    for (int i = 1; i <= n; i++) {
        l[i] = std::lower_bound(v + 1, v + vcnt + 1, l[i]) - v;
        r[i] = std::lower_bound(v + 1, v + vcnt + 1, r[i]) - v;
        bit1::mdf(l[i], r[i]);
        bit2::mdf(r[i], l[i]);
        id[i] = i;
    }
    std::sort(id + 1, id + n + 1, [](int x, int y) { return r[x] < r[y]; });
    for (int i = 1, cur = 1; i <= vcnt; i++) {
        zmt::root[i] = zmt::root[i - 1];
        for (; cur <= n && r[id[cur]] == i; cur++) {
            zmt::root[i] = zmt::modify(zmt::root[i], 1, vcnt, l[id[cur]], v[r[id[cur]]] - v[l[id[cur]]]);
        }
    }
    for (int i = 1; i <= m; i++) {
        int now = 0;
        a[i] = std::lower_bound(v + 1, v + vcnt + 1, a[i]) - v;
        b[i] = std::lower_bound(v + 1, v + vcnt + 1, b[i]) - v;
        now = std::max(now, std::min(v[bit1::qry(a[i])], v[b[i]]) - v[a[i]]);
        now = std::max(now, v[b[i]] - std::max(v[bit2::qry(b[i])], v[a[i]]));
        now = std::max(now, zmt::query(zmt::root[b[i]], 1, vcnt, a[i], vcnt));
        ans = std::max(ans, 1LL * now * c[i]);
    }
    io.put(ans, '\n');
    return 0;
}