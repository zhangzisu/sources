#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
const int MAXN = 100010, INF = (~0U) >> 1;
inline int getint() {
    int r = 0, s = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-') s = 0;
    for (; isdigit(c); c = getchar()) r = (((r << 2) + r) << 1) + (c ^ '0');
    return s ? r : -r;
}
struct point {
    int x, y;
    inline friend point operator+(const point &a, const point &b) {
        point c;
        c.x = a.x + b.x;
        c.y = a.y + b.y;
        return c;
    }
    inline friend point operator-(const point &a, const point &b) {
        point c;
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        return c;
    }
} A[MAXN], B[MAXN], C[MAXN], S[MAXN];
int top;
inline bool cmp0(const point &a, const point &b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}
inline bool cmp1(const point &a, const point &b) {
    double alpha = atan2(a.y - C[1].y, a.x - C[1].x);
    double beta = atan2(b.y - C[1].y, b.x - C[1].x);
    if (alpha == beta) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
    return alpha < beta;
}
inline int cross(const point &a, const point &b, const point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
}
void Graham(int all) {
    C[0] = (point){INF, INF};
    int k;
    for (int i = 1; i <= all; i++)
        if (C[0].y > C[i].y || (C[0].y == C[i].y && C[i].x < C[0].x)) C[0] = C[i], k = i;
    std::swap(C[k], C[1]);
    std::sort(C + 2, C + all + 1, cmp1);
    //for(int i = 1;i <= all;i++) C[i].print();
    S[0] = C[1], S[1] = C[2];
    top = 1;
    for (int i = 3; i <= all;) {
        if (top && cross(S[top - 1], C[i], S[top]) >= 0)
            top--;
        else
            S[++top] = C[i++];
    }
}
inline int sqr(const point &a, const point &b, const point &c) {
    int x1 = b.x - a.x, y1 = b.y - a.y, x2 = c.x - a.x, y2 = c.y - a.y;
    return std::abs(y2 * x1 - y1 * x2);
}
int main() {
    freopen("gubugu.in", "r", stdin);
    freopen("gubugu.out", "w", stdout);
    int n = getint(), m = getint(), all = n * m;
    for (int i = 1, x, y; i <= n; i++) x = getint(), y = getint(), A[i] = (point){x, y};
    for (int i = 1, x, y; i <= m; i++) x = getint(), y = getint(), B[i] = (point){x, y};
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) C[++cnt] = A[i] + B[j];
    Graham(all);
    std::sort(S, S + top + 1, cmp0);
    for (int i = 1; i <= top; i++) S[i] = S[i] - S[0];
    std::sort(S + 1, S + top + 1, cmp1);
    int ans = 0;
    for (int i = 1; i <= top - 1; i++) {
        ans += sqr(S[0], S[i], S[i + 1]);
    }
    printf("%d\n", ans);
    return 0;
}
