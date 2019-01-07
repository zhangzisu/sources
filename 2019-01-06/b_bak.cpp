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
} io(fopen("b.in", "r"), fopen("b.out", "w"));
#define MAXN 100010
#define MOD 1000000007
#define INV
inline int trim(int x) { return x -= MOD, x += (x >> 31) & MOD; }
namespace jzm {
struct tag_t {
    int a, b;
    inline tag_t(int a = 0, int b = 0) : a(a), b(b) {}
    inline tag_t friend operator+(tag_t a, tag_t b) {
        return tag_t(trim(a.a + b.a), trim(a.b + b.b));
    }
} tag[MAXN << 2];
int sum[MAXN << 2];
inline int calc(int start, int end, int delta, int offset) {
    return (1LL * (start + end) * delta + 2LL * offset) % MOD * (end - start + 1) % MOD * 500000004 % MOD;
}
inline int pushDown(int n, int l, int r) {
    int mid = (l + r) >> 1;
    sum[n << 1] = trim(sum[n << 1] + calc(l, mid, tag[n].a, tag[n].b));
    sum[n << 1 | 1] = trim(sum[n << 1 | 1] + calc(mid + 1, r, tag[n].a, tag[n].b));
    tag[n << 1] = tag[n << 1] + tag[n];
    tag[n << 1 | 1] = tag[n << 1 | 1] + tag[n];
    tag[n] = tag_t(0, 0);
    return mid;
}
inline int query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[n];
    int mid = pushDown(n, l, r);
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return trim(query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline void add(int n, int l, int r, int L, int R, tag_t v) {
    if (l == L && r == R) {
        sum[n] = trim(sum[n] + calc(l, r, v.a, v.b));
        tag[n] = tag[n] + v;
        return;
    }
    int mid = pushDown(n, l, r);
    if (R <= mid) {
        add(n << 1, l, mid, L, R, v);
    } else if (L > mid) {
        add(n << 1 | 1, mid + 1, r, L, R, v);
    } else {
        add(n << 1, l, mid, L, mid, v);
        add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    }
    sum[n] = trim(sum[n << 1] + sum[n << 1 | 1]);
}
}  // namespace jzm
namespace hls {
struct tag_t {
    int a, b;
    inline tag_t(int a = 0, int b = 0) : a(a), b(b) {}
    inline int valueAt(int x) {
        return a * x + b;
    }
} tag[MAXN << 2];
inline void change(int n, int l, int r, tag_t v) {
    if (l == r) {
        if (v.valueAt(l) > tag[n].valueAt(l)) tag[n] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(v.a > tag[n].a){
        if(v.valueAt(mid) > tag[n].valueAt(mid)){
            tag[n] = v;
            change(n << 1, l, mid, v);
        }else{
            change(n << 1 | 1, mid + 1, r, v);
        }
    }else{
        if(v.valueAt(mid) > tag[n].valueAt(mid)){
            tag[n] = v;
            change(n << 1 | 1, mid + 1, r, v);
        }else{
            change(n << 1, l, mid, v);
        }
    }
}
inline void modify(int n, int l, int r, int L, int R, tag_t v) {
    if (l == L && r == R) return change(n, l, r, v);
    int mid = (l + r) >> 1;
    if (R <= mid) return modify(n << 1, l, mid, L, R, v);
    if (L > mid) return modify(n << 1 | 1, mid + 1, r, L, R, v);
    modify(n << 1, l, mid, L, mid, v);
    modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
inline int query(int n, int l, int r, int p) {
    int ret = tag[n].valueAt(p);
    do {
        int mid = (l + r) >> 1;
        if (p <= mid) {
            r = mid;
            n = n << 1;
        } else {
            l = mid + 1;
            n = n << 1 | 1;
        }
        ret = std::max(ret, tag[n].valueAt(p));
    } while (l < r);
    return ret;
}
}  // namespace hls
int n = io.getint(), m = io.getint();
int main() {
    for (int op, l, r, a, b; m; m--) {
        op = io.getint();
        if (op == 1) {
            l = io.getint(), r = io.getint(), a = io.getint(), b = io.getint();
            hls::modify(1, 1, n, l, r, hls::tag_t(b, a - l * b));
        } else if (op == 2) {
            l = io.getint(), r = io.getint(), a = io.getint(), b = io.getint();
            jzm::add(1, 1, n, l, r, jzm::tag_t(b, trim(a + MOD - 1LL * l * b % MOD)));
        } else if (op == 3) {
            l = io.getint(), r = io.getint();
            io.put(jzm::query(1, 1, n, l, r), '\n');
        } else if (op == 4) {
            a = io.getint();
            int max = hls::query(1, 1, n, a);
            max = trim(max + jzm::query(1, 1, n, a, a));
            io.put(max, '\n');
        }
    }
    return 0;
}
// int main() {
//     for (int op, l, r, a, b; m; m--) {
//         op = io.getint();
//         if (op == 1) {
//             l = io.getint(), r = io.getint(), a = io.getint(), b = io.getint();
//             jzm::add(1, 1, n, l, r, jzm::tag_t(b, a - l * b));
//         } else if (op == 2) {
//             l = io.getint(), r = io.getint();
//             io.put(jzm::query(1, 1, n, l, r), '\n');
//         }
//     }
//     return 0;
// }