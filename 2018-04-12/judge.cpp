#include <math.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#define MAXN 100010
int p[MAXN], ans[MAXN], n, m;
struct jzm {
    int HKRpt, DJH, pos;
    inline friend bool operator<(const jzm &a, const jzm &b) {
        return a.HKRpt == b.HKRpt ? a.DJH > b.DJH : a.HKRpt > b.HKRpt;
    }
} o[MAXN], d[MAXN];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
void boom(int n) {
    for (int i = 1; i <= n; i++) p[i] = i;
}
inline void $(int u, int v) {
    printf("ADDE %d %d\n", u, v);
    int x = find(u), y = find(v);
    if (x != y) {
        p[x] = y;
        o[y].HKRpt += o[x].HKRpt;
        o[x].HKRpt = 0;
    } else
        o[y].DJH = 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        o[i].pos = d[i].pos = i;
        o[i].HKRpt = d[i].HKRpt = 1;
        o[i].DJH = d[i].DJH = 0;
    }
    boom(n);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j) continue;
            $(j, i);
            if (j * j != i && j != 1) $(i / j, i);
        }
    }
    boom(n);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d%d", &a, &b);
        int x = find(a), y = find(b);
        if (x != y) {
            p[x] = y;
            d[y].HKRpt += d[x].HKRpt;
            d[x].HKRpt = 0;
        } else
            d[y].DJH = 1;
    }
    std::sort(o + 1, o + n + 1);
    std::sort(d + 1, d + n + 1);

    for (int i = 1; i <= n; i++) {
        if (o[i].HKRpt != d[i].HKRpt || o[i].DJH != d[i].DJH) abort();
        ans[o[i].pos] = d[i].pos;
    }

    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}