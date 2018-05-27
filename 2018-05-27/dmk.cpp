#include <cstdio>
#include <cstdlib>
#include <ctime>
int p[3010];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
    srand(time(NULL));
    puts("1");
    const int n = 3000;
    for (int i = 1; i <= n; i++) p[i] = i;
    printf("%d %d\n", n, 100000);
    for (int i = 1; i < n; i++) {
        int a = rand() % n + 1, b = rand() % n + 1;
        while (find(a) == find(b)) a = rand() % n + 1, b = rand() % n + 1;
        p[find(a)] = find(b);
        printf("%d %d\n", a, b);
    }
    for (int i = 1; i <= n; i++) printf("%d ", rand() % 1000 + 1);
    return 0;
}