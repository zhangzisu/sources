#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
const int MOD = 9977;
const int N = 10;
inline int rrnd() {
    return (rand() << 2) | (rand() & ((1 << 2) - 1));
}
int main() {
    srand(time(NULL));
    printf("%d %d %d\n", N, N, MOD);
    for (int i = 0; i < N; i++) {
        int l = rrnd() % N, r = rrnd() % N;
        while (l > r) l = rrnd() % N, r = rrnd() % N;
        printf("%d %d %d\n", rand() & 1, l + 1, r + 1);
    }
}