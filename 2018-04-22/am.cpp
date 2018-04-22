#include <cstdio>
#include <cstdlib>
#include <ctime>
const int n = 10, m = 10;
int p[n + 10];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
    srand(time(NULL));
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i < n; i++) {
        int a = rand() % n + 1, b = rand() % n + 1;
        while (find(a) == find(b)) a = rand() % n + 1, b = rand() % n + 1;
        printf("%d %d\n", a, b);
        p[find(a)] = b;
    }
    for (int i = 1; i <= m; i++) printf("%d %d\n", 1 + (rand() & 1), rand() % n + 1);
    return 0;
}