#include <math.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
int pre[10100], ans[10010];
struct e {
    int a, b, id;
};
e s1[10010];
e s2[10010];
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
int cmp(e a, e b) {
    if (a.a == b.a)
        return a.b > b.b;
    else
        return a.a > b.a;
}
void init(int n) {
    for (int i = 1; i <= n; i++)
        pre[i] = i;
}
int n, m;
int main() {
    for (int i = 1; i < 10010; i++) {
        s1[i].a = 1;
        s1[i].b = 0;
        s2[i].a = 1;
        s2[i].b = 0;
        s1[i].id = s2[i].id = i;
    }
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int dx = find(a);
        int dy = find(b);
        if (dx != dy) {
            pre[dx] = dy;
            s1[dy].a += s1[dx].a;
            s1[dx].a = 0;
        } else
            s1[dy].b = 1;
    }
    init(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int dx = find(a);
        int dy = find(b);
        if (dx != dy) {
            pre[dx] = dy;
            s2[dy].a += s2[dx].a;
            s2[dx].a = 0;
        } else
            s2[dy].b = 1;
    }
    sort(s1 + 1, s1 + n + 1, cmp);
    sort(s2 + 1, s2 + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        ans[s1[i].id] = s2[i].id;
    }
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}