#include <stdio.h>
#define ALL 4294967296U
#define QUEUE 10000
#define next(x) (((x) + 1) % QUEUE)
#define short __int16_t
#define int __int32_t
short n, i, j, x, y;
int ans, h, t, queue[QUEUE];
unsigned pool[31250];
int get(int id) { return (pool[id >> 5] >> (id & 31)) & 1; }
void set(int id) { pool[id >> 5] |= (1 << (id & 31)); }
int _(short x, short y) { return (int)x * n + y; }
int main() {
    // freopen("Part.in", "r", stdin);
    // freopen("Part.out", "w", stdout);
    scanf("%hd", &n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &ans);
            if (ans) set(_(i, j));
        }
    }
    ans = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (get(_(i, j))) continue;
            ans++;
            fprintf(stderr, "(%d, %d)\n", i, j);
            set(queue[h = t = 0] = _(i, j));
            while (h != next(t)) {
                x = queue[h] / n;
                y = queue[h] % n;
                h = next(h);
                if (x > 0 && !get(_(x - 1, y))) set(queue[t = next(t)] = _(x - 1, y));
                if (x < n - 1 && !get(_(x + 1, y))) set(queue[t = next(t)] = _(x + 1, y));
                if (y > 0 && !get(_(x, y - 1))) set(queue[t = next(t)] = _(x, y - 1));
                if (y < n - 1 && !get(_(x, y + 1))) set(queue[t = next(t)] = _(x, y + 1));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}