#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int x;
int main() {
    scanf("%d", &x);
    for (int i = 2; i <= x; i++) {
        if (x == 1) break;
        if (x % i) continue;
        while (x % i == 0) printf("%d ", i), x /= i;
    }
    puts("");
    return 0;
}