#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, k;
struct data {
    int a, b, c;
    inline data(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
    inline friend bool operator<(const data& a, const data& b) { return a.a < b.a; }
} dt[MAXN];
struct node {
    int l, r, sum;
} sg[MAXN];
inline void insert(int& n, int l, int r, int p) {
    //
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &dt[i].a, &dt[i].b, &dt[i].c);
    std::sort(dt + 1, dt + n + 1);
    for (int i = 1; i <= n; i++) {
        //
    }
    return 0;
}