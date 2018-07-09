#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

const int N = 50;
const int M = 5000;

int main() {
    printf("%d %d\n", N, M);
    for (int i = 1; i <= M; i++) printf("%d %d\n", rand() % N + 1, rand() % N + 1);
    return 0;
}