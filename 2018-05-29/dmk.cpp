#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    const int n = 20;
    printf("%d\n", n);
    const int m = 1 << n;
    for (int i = 0; i < m; i++) puts("1000");
    return 0;
}