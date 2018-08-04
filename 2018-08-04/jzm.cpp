#include <bitset>
#include <cstdio>
std::bitset<1000001000> vis;
const int n = 1000001000;
int pri[n / 32], all = 0;
int main() {
    for (int i = 2; i < n; i++) {
        if (!vis[i]) {
            pri[++all] = i;
        }
        for (int j = 1; j <= all; j++) {
            if (1LL * i * pri[j] >= n) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
        if (i % 10000000 == 0) fprintf(stderr, "PROCESSED %d NUMBERS\n", i);
    }
    for (int i = all, j = 0; i && j <= 2000; i--, j++) printf("%d\n", pri[i]);
}