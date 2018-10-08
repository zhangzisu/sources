#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a, n, k, ans, head, tail;
struct node {
    int d, now, vis;
    inline node(int d = 0, int now = 0, int vis = 0) : d(d), now(now), vis(vis) {}
} Q[100000000];
inline int next(int x) {
    return x == 99999999 ? 0 : x + 1;
}
void bfs() {
    Q[head = tail = 0] = node(n, 0, 0);
    while (head != next(tail)) {
        node &tmp = Q[head];
        head = next(head);
        if (tmp.d) {
            if (!tmp.vis) {
                tail = next(tail);
                Q[tail].d = tmp.d - 1;
                Q[tail].now = Q[tail].vis = 0;
            }
            for (int i = !tmp.vis; i < a; i++) {
                if ((tmp.vis >> i) & 1) continue;
                tail = next(tail);
                Q[tail].d = tmp.d - 1;
                Q[tail].now = tmp.now * a + i;
                Q[tail].vis = tmp.vis | (1 << i);
            }
        } else {
            ans += (tmp.now % k == 0);
        }
    }
}
int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    scanf("%d%d%d", &a, &n, &k);
    n = std::min(n, a);
    bfs();
    printf("%d\n", ans - 1);
    return 0;
}