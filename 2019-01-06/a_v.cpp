#include <cstdio>
int main() {
    for (long long i = 1; i <= 100000; i++) {
        if ((i) * (2 * i + 1) * (i + 1) % 6 != 0) {
            puts("ERR");
            return 1;
        }
    }
}