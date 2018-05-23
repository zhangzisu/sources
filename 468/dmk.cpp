#include <cstdio>
#include <cstdlib>
#include <ctime>
const int n = 10;
int p[n + 1];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
    srand(time(NULL));
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i < n; i++) {
        int x = rand() % n + 1, y = rand() % n + 1;
        while (find(x) == find(y)) x = rand() % n + 1, y = rand() % n + 1;
        p[find(x)] = find(y);
        printf("%d %d %d\n", x, y, rand());
    }
}