#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

int main() {
    srand(time(NULL));
    int n = 3000;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) printf("%d ", rand() % 3);
}